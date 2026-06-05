#include "doctest.h"
#include "Mat4.h"


TEST_CASE("Create and validate identity Matrix"){

    Mat4 m;

    //checks for all values in loop
    for (int row = 0; row < 4; row++) {
        for (int col = 0; col < 4; col++) {
            if (row == col) {
                CHECK(m.matrix[row][col] == doctest::Approx(1.0).epsilon(1e-9));
            } else {
                CHECK(m.matrix[row][col] == doctest::Approx(0.0).epsilon(1e-9));
            }
        }
    }
}

TEST_CASE("Transform Vec3 with Identity Matrix, Vec3 remains the same"){

    Mat4 m;
    Vec3 initial{1.0, 2.0, 3.0};
    double w = 1.0;

    Vec3 got = m.transform(initial, w);

    CHECK(got.x == doctest::Approx(initial.x).epsilon(1e-9));
    CHECK(got.y == doctest::Approx(initial.y).epsilon(1e-9));
    CHECK(got.z == doctest::Approx(initial.z).epsilon(1e-9));
}

TEST_CASE("Transform Vec3 with non identity Matrix and w=1, Vec3 changes translation applied"){
    
    Mat4 m;

    m.matrix[0][3] = 3.0;
    m.matrix[1][3] = 2.0;
    m.matrix[2][3] = 3.0;

    Vec3 initial{1.0, 2.0, 3.0};
    Vec3 want{4.0, 4.0, 6.0};
    double w = 1.0;

    Vec3 got = m.transform(initial, w);

    CHECK(got.x == doctest::Approx(want.x).epsilon(1e-9));
    CHECK(got.y == doctest::Approx(want.y).epsilon(1e-9));
    CHECK(got.z == doctest::Approx(want.z).epsilon(1e-9));
}

TEST_CASE("Transform Vec3 with non identity Matrix and w=0, resulted Vec3 changes translation not applied"){
    
    Mat4 m;

    m.matrix[0][3] = 3.0;
    m.matrix[1][3] = 2.0;
    m.matrix[2][3] = 3.0;

    Vec3 initial{1.0, 2.0, 3.0};
    double w = 0.0;
    
    Vec3 got = m.transform(initial, w);

    CHECK(got.x == doctest::Approx(initial.x).epsilon(1e-9));
    CHECK(got.y == doctest::Approx(initial.y).epsilon(1e-9));
    CHECK(got.z == doctest::Approx(initial.z).epsilon(1e-9));
}

TEST_CASE("translate() sets correct values in last column"){
    
    Mat4 m;
    Vec3 v{2.0, 3.0, 4.0};

    Mat4 got = m.translate(v.x, v.y, v.z);

    CHECK(got.matrix[0][3] == doctest::Approx(v.x).epsilon(1e-9));
    CHECK(got.matrix[1][3] == doctest::Approx(v.y).epsilon(1e-9));
    CHECK(got.matrix[2][3] == doctest::Approx(v.z).epsilon(1e-9));
    CHECK(got.matrix[3][3] == doctest::Approx(1.0).epsilon(1e-9));
}

TEST_CASE("With w=0, vector has not changed and the direction is not translated"){
    
    Mat4 m;
    Vec3 initial{2.0, 3.0, 4.0};
    double w = 0.0;

    Vec3 got = m.translate(initial.x, initial.y, initial.z).transform(initial, w);

    CHECK(got.x == doctest::Approx(initial.x).epsilon(1e-9));
    CHECK(got.y == doctest::Approx(initial.y).epsilon(1e-9));
    CHECK(got.z == doctest::Approx(initial.z).epsilon(1e-9));
}

TEST_CASE("scale() sets correct values on diagonal"){
    
    Mat4 m;
    Vec3 v{2.0, 3.0, 4.0};

    Mat4 got = m.scale(v.x, v.y, v.z);

    CHECK(got.matrix[0][0] == doctest::Approx(v.x).epsilon(1e-9));
    CHECK(got.matrix[1][1] == doctest::Approx(v.y).epsilon(1e-9));
    CHECK(got.matrix[2][2] == doctest::Approx(v.z).epsilon(1e-9));
    CHECK(got.matrix[3][3] == doctest::Approx(1.0).epsilon(1e-9));
}

TEST_CASE("scale() transforms unit vector correctly"){
    
    Mat4 m;
    Vec3 initial{2.0, 3.0, 4.0};
    double w = 1.0;

    Vec3 got = m.scale(initial.x, initial.y, initial.z).transform(Vec3{1.0, 1.0, 1.0}, w);

    CHECK(got.x == doctest::Approx(initial.x).epsilon(1e-9));
    CHECK(got.y == doctest::Approx(initial.y).epsilon(1e-9));
    CHECK(got.z == doctest::Approx(initial.z).epsilon(1e-9));
}