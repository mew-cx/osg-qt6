#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QApplication>
#include <QMainWindow>
#include <QTimer>

#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

class OSGWidget: public QOpenGLWidget, protected QOpenGLFunctions {

Q_OBJECT

public:
	OSGWidget(QWidget* parent=nullptr):
	QOpenGLWidget(parent) {
		_timer = new QTimer(this);

		// connect(_timer, &QTimer::timeout, this, &OSGWidget::update);
		// connect(_timer, &QTimer::timeout, this, QOverload<>::of(&OSGWidget::repaint));
		connect(_timer, &QTimer::timeout, this, QOverload<>::of(&OSGWidget::update));

		_timer->start(1000 / 60);
	}

protected:
	void initializeGL() override {
		OSG_WARN << "initializeGL" << std::endl;

		_viewer = new osgViewer::Viewer();

		_viewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
		_viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
		_viewer->setSceneData(osgDB::readNodeFile("cow.osgt"));
		_viewer->setCameraManipulator(new osgGA::TrackballManipulator());

		// TODO: Just letting QT6 "do its own thing" here seems to work much better. Need to
		// investigate this for more complex setups.
		/* osg::GraphicsContext::Traits* traits = new osg::GraphicsContext::Traits();

		traits->x = 0;
		traits->y = 0;
		traits->width = width();
		traits->height = height();
		traits->windowDecoration = false;
		traits->doubleBuffer = true;
		traits->sharedContext = 0;
		traits->setInheritedWindowPixelFormat = true;

		osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits);

		osg::Camera* camera = _viewer->getCamera();

		camera->setGraphicsContext(gc.get());
		camera->setViewport(new osg::Viewport(0, 0, width(), height()));
		camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width()) / height(), 1.0, 1000.0); */
	}

	void resizeGL(int w, int h) override {
		OSG_WARN << "resizeGL: " << w << " x " << h << std::endl;

		_viewer->getCamera()->setViewport(new osg::Viewport(0, 0, w, h));
		_viewer->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(w) / h, 1.0, 1000.0);
	}

	void paintGL() override {
		OSG_WARN << "paintGL" << std::endl;

		_viewer->frame();
	}

private:
	osg::ref_ptr<osgViewer::Viewer> _viewer;

	QTimer* _timer = nullptr;
};

int main(int argc, char** argv) {
	QApplication app(argc, argv);

	QMainWindow mainWindow;

	OSGWidget* osgWidget = new OSGWidget();

	mainWindow.setCentralWidget(osgWidget);
	mainWindow.resize(800, 600);
	mainWindow.show();

	return app.exec();
}

#include "example-osg.moc"
