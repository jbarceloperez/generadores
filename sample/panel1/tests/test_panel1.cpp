#include "gtest/gtest.h"

#include <QApplication>
#include <QObject>
#include <QPushButton>
#include <QTest>
#include <QSignalSpy>

#include "../src_inc/panel1.h"

// Definir la clase test fixture.
class panel1Test : public ::testing::Test 
{
protected:
    // Declarar objetos o variables para los tests
    QApplication *app;
    panel1 *obj;

    void SetUp() override 
    {
        int argc = 0;
        char *argv[] = {(char *)"test"};
        app = new QApplication(argc, argv);

        obj = new panel1();
        obj->show();
    }

    void TearDown() override 
    {
        // Limpiar
        obj->close();
        delete obj;

        delete app;
    }

};

// Definir los tests.

TEST_F(panel1Test, Test_pbApply) 
{
    QPushButton *button = obj->findChild<QPushButton *>("pbApply");
    ASSERT_NE(button, nullptr);

    // Usar QSignalSpy para monitorear la señal clicked del botón
    QSignalSpy spy(button, &QPushButton::clicked);
    QTest::mouseClick(button, Qt::LeftButton, Qt::NoModifier);

    ASSERT_EQ(spy.count(), 1);
}


TEST_F(panel1Test, Test_pbCancel) 
{
    QPushButton *button = obj->findChild<QPushButton *>("pbCancel");
    ASSERT_NE(button, nullptr);

    // Usar QSignalSpy para monitorear la señal clicked del botón
    QSignalSpy spy(button, &QPushButton::clicked);
    QTest::mouseClick(button, Qt::LeftButton, Qt::NoModifier);

    ASSERT_EQ(spy.count(), 1);
}
