
#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QApplication>
#include <QMainWindow>
#include <QTimer>

#include <osgDB/ReadFile>

#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>

#include <osgEarth/MapNode>
#include <osgEarth/ImageLayer>
#include <osgEarth/GDAL>
#include <osgEarth/EarthManipulator>
#include <osgEarth/ExampleResources>

#include <iostream>

#include <osgEarth/Metrics>

//#define LC "[viewer] "

/////////////////////////////////////////////////////////////////////////////
// osgearth-viewer

using namespace osgEarth;
using namespace osgEarth::Util;

int
main(int argc, char** argv)
{
    osg::ArgumentParser arguments(&argc,argv);

    osgEarth::initialize(arguments);
    osgViewer::Viewer viewer(arguments);
    viewer.setCameraManipulator(new EarthManipulator(arguments));
    viewer.getCamera()->setSmallFeatureCullingPixelSize(-1.0f);
    auto node = MapNodeHelper().load(arguments, &viewer);
    if (node.valid())
    {
        if (MapNode::get(node))
        {
            viewer.setSceneData(node);
            return viewer.run();
        }
    }
}

/////////////////////////////////////////////////////////////////////////////

class OSGWidget: public QOpenGLWidget, protected QOpenGLFunctions {

Q_OBJECT

public:
	OSGWidget(QWidget* parent=nullptr): QOpenGLWidget(parent) {
		_timer = new QTimer(this);

		// connect(_timer, &QTimer::timeout, this, &OSGWidget::update);
		// connect(_timer, &QTimer::timeout, this, QOverload<>::of(&OSGWidget::repaint));
		connect(_timer, &QTimer::timeout, this, QOverload<>::of(&OSGWidget::update));

		_timer->start(1000 / 60);
	}

protected:
	void initializeGL() override {
		OSG_WARN << "initializeGL" << std::endl;

		osgEarth::initialize();

		osgEarth::Map* map = new osgEarth::Map();

		osgEarth::MapNode* node = new osgEarth::MapNode(map);

		_viewer = new osgViewer::Viewer();
		_viewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
		_viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
		_viewer->setCameraManipulator(new osgEarth::EarthManipulator());
		_viewer->setSceneData(node);

		osgEarth::MapNodeHelper().configureView(_viewer);
	}

	void resizeGL(int w, int h) override {
		OSG_WARN << "resizeGL: " << w << " x " << h << std::endl;

		_viewer->getCamera()->setViewport(new osg::Viewport(0, 0, w, h));
		_viewer->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(w) / h, 1.0, 1000.0);
	}

	void paintGL() override {
		OSG_WARN << "paintGL" << std::endl;

		// TODO: This is important! I'm still investigating what value is actually being implied by
		// `defaultFramebufferObject()` here; however, this simple example SEEMS to work without it.
		// I imagine anything but the most trivial osgEarth examples will need to address this.
		// _viewer->getCamera()->getGraphicsContext()->setDefaultFboId(defaultFramebufferObject());
		_viewer->frame();
	}

private:
	osg::ref_ptr<osgViewer::Viewer> _viewer;

	QTimer* _timer = nullptr;
};

/////////////////////////////////////////////////////////////////////////////

int mainQ(int argc, char** argv) {
	QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

	QApplication app(argc, argv);

	QMainWindow mainWindow;

	OSGWidget* osgWidget = new OSGWidget();

	mainWindow.setCentralWidget(osgWidget);
	mainWindow.resize(800, 600);
	mainWindow.show();

	return app.exec();
}

#include "example-osgearth.moc"
