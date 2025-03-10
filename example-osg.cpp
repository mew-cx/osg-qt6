#include <QOpenGLWidget>
#include <QApplication>
#include <QMainWindow>
#include <QTimer>

#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>
#include <osgGA/TrackballManipulator>
#include <osgDB/ReadFile>

class OSGWidget: public QOpenGLWidget {

Q_OBJECT

public:
	OSGWidget(QWidget* parent=nullptr):
	QOpenGLWidget(parent) {
		// Set up a timer to refresh the scene 60 times per second
		_timer = new QTimer(this);

		// connect(_timer, &QTimer::timeout, this, &OSGWidget::update);
		// connect(_timer, &QTimer::timeout, this, QOverload<>::of(&OSGWidget::repaint));
		connect(_timer, &QTimer::timeout, this, QOverload<>::of(&OSGWidget::update));

		_timer->start(1000 / 60); // 60 FPS
	}

protected:
	void initializeGL() override {
		_viewer = new osgViewer::Viewer();

		_viewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
		_viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
		_viewer->setSceneData(osgDB::readNodeFile("cow.osgt"));
		_viewer->setCameraManipulator(new osgGA::TrackballManipulator());

		// Create an OSG Graphics Context that shares Qt's OpenGL context
		osg::GraphicsContext::Traits* traits = new osg::GraphicsContext::Traits();

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
		camera->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width()) / height(), 1.0, 1000.0);
	}

	void resizeGL(int w, int h) override {
		_viewer->getCamera()->setViewport(new osg::Viewport(0, 0, w, h));
		_viewer->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(w) / h, 1.0, 1000.0);
	}

	void paintGL() override {
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
