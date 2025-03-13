#include <QOpenGLWidget>
#include <QOpenGLFunctions>
#include <QApplication>
#include <QMainWindow>
#include <QTimer>

#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/ShapeDrawable>
#include <osg/Point>
#include <osg/PolygonMode>
#include <osgGA/TrackballManipulator>
#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>

namespace osg_qt6 {

using vec_t = osg::Vec3::value_type;

osg::ShapeDrawable* createSphere(vec_t radius, vec_t pSize) {
	osg::ShapeDrawable* s = new osg::ShapeDrawable(new osg::Sphere(
		osg::Vec3(0.0, 0.0, 0.0),
		radius
	));

	s->getOrCreateStateSet()->setAttribute(
		new osg::Point(pSize),
		osg::StateAttribute::ON
	);

	return s;
}

osg::MatrixTransform* createSphereAt(const osg::Vec3& pos, vec_t radius, vec_t pSize) {
	osg::MatrixTransform* m = new osg::MatrixTransform(osg::Matrix::translate(pos));
	osg::Geode* g = new osg::Geode();

	g->addDrawable(createSphere(radius, pSize));

	m->addChild(g);

	return m;
}

}

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

		osg::Group* root = new osg::Group();

		root->addChild(osg_qt6::createSphereAt(osg::Vec3(), 10.0, 2.0));
		root->getOrCreateStateSet()->setAttributeAndModes(
			new osg::PolygonMode(osg::PolygonMode::FRONT_AND_BACK, osg::PolygonMode::POINT),
			osg::StateAttribute::ON
		);

		_viewer = new osgViewer::Viewer();

		_viewer->setUpViewerAsEmbeddedInWindow(0, 0, width(), height());
		_viewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);
		_viewer->setSceneData(root);
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
	QCoreApplication::setAttribute(Qt::AA_UseDesktopOpenGL);

	QApplication app(argc, argv);

	QMainWindow mainWindow;

	OSGWidget* osgWidget = new OSGWidget();

	mainWindow.setCentralWidget(osgWidget);
	mainWindow.resize(800, 600);
	mainWindow.show();

	return app.exec();
}

#include "example-osg.moc"
