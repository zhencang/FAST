#include "FAST/Testing.hpp"
#include "FAST/Importers/ImageFileImporter.hpp"
#include "FAST/Algorithms/ImageResampler/ImageResampler.hpp"
#include "FAST/Visualization/ImageRenderer/ImageRenderer.hpp"
#include "FAST/Visualization/SimpleWindow.hpp"

using namespace fast;

TEST_CASE("ImageResampler 2D", "[fast][ImageResampler][visual]") {
    ImageFileImporter::pointer importer = ImageFileImporter::New();
    importer->setFilename(Config::getTestDataPath() + "US/CarotidArtery/Left/US-2D_400.mhd");

    ImageResampler::pointer resampler = ImageResampler::New();
    resampler->setOutputSpacing(0.1f, 0.1f);
    resampler->setInputConnection(importer->getOutputPort());

    ImageRenderer::pointer renderer = ImageRenderer::New();
    renderer->addInputConnection(resampler->getOutputPort());

    SimpleWindow::pointer window = SimpleWindow::New();
    window->addRenderer(renderer);
    window->set2DMode();
    window->setTimeout(500);
    window->start();
}

TEST_CASE("ImageResampler 3D CT", "[fast][ImageResampler][visual]") {
    ImageFileImporter::pointer importer = ImageFileImporter::New();
    importer->setFilename(Config::getTestDataPath() + "CT/CT-Abdomen.mhd");

    ImageResampler::pointer resampler = ImageResampler::New();
    resampler->setOutputSpacing(1.0f, 1.0f, 1.0f);
    resampler->setInputConnection(importer->getOutputPort());

    ImageRenderer::pointer renderer = ImageRenderer::New();
    renderer->addInputConnection(resampler->getOutputPort());

    SimpleWindow::pointer window = SimpleWindow::New();
    window->addRenderer(renderer);
    window->set2DMode();
    window->getView()->setViewingPlane(Plane::Coronal());
    window->setTimeout(500);
    window->start();
}