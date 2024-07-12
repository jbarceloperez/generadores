#include "gtest/gtest.h"

#include "../src_inc/panel1.h"

// Definir la clase test fixture.
class panel1Test : public ::testing::Test 
{
protected:
    panel1Test()
    {
        // Constructor
        obj = new panel1();
    }

    void SetUp() override 
    {
        // Inicializar
    }

    void TearDown() override 
    {
        // Limpiar
        delete obj;
    }

    // Declarar objetos o variables para los tests
    panel1* obj;
};

// Definir los tests.
TEST_F(panel1Test, TestFunction1) 
{
    // Call the function you want to test.
    // ...

    // Assert that the function behaves as expected.
    // ...  
    ASSERT_EQ(1, 1);  
}

int main(int argc, char **argv) 
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}