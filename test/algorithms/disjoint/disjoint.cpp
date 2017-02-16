// Boost.Geometry

// Copyright (c) 2016 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#define BOOST_GEOMETRY_TEST_DEBUG

#include <boost/geometry/geometries/box.hpp>
#include <boost/geometry/geometries/point_xy.hpp>
#include <boost/geometry/geometries/geometries.hpp>
#include <boost/geometry/geometries/adapted/c_array.hpp>
#include <boost/geometry/geometries/adapted/boost_tuple.hpp>
#include <test_common/test_point.hpp>

#include <boost/geometry/formulas/andoyer_inverse.hpp>
#include <boost/geometry/formulas/thomas_inverse.hpp>
#include <boost/geometry/formulas/vincenty_inverse.hpp>

#include <boost/geometry/strategies/strategies.hpp>

#include <boost/geometry/algorithms/disjoint.hpp>

#include <geometry_test_common.hpp>

#include "test_disjoint.hpp"

namespace bg = boost::geometry;

//Tests for disjoint(point, box), disjoint(box, box) and disjoint(segment, box)

template <typename P>
void disjoint_tests_1()
{
    test_disjoint<bg::model::box<P>, P>("BOX(1 1,3 3)", "POINT(4 4)", true);
    test_disjoint<bg::model::box<P>, P>("BOX(1 1,3 3)", "POINT(2 2)", false);
    test_disjoint<bg::model::box<P>, P>("BOX(1 1,3 3)", "POINT(3 3)", false);
    test_disjoint<bg::model::box<P>, P>("BOX(1 1,3 3)", "POINT(2 3)", false);

    test_disjoint<bg::model::box<P>, bg::model::box<P> >("BOX(1 1,3 3)",
                                                         "BOX(1 4,5 5)",
                                                         true);
    test_disjoint<bg::model::box<P>, bg::model::box<P> >("BOX(1 1,3 3)",
                                                         "BOX(2 2,4 4)",
                                                         false);
    test_disjoint<bg::model::box<P>, bg::model::box<P> >("BOX(1 1,3 3)",
                                                         "BOX(3 3,4 4)",
                                                         false);
    test_disjoint<bg::model::box<P>, bg::model::box<P> >("BOX(1 1,3 3)",
                                                         "BOX(2 3,4 4)",
                                                         false);

    test_disjoint<bg::model::box<P>, bg::model::segment<P> >("BOX(1 1,3 3)",
                                                             "SEGMENT(1 4, 5 5)",
                                                             true);
    test_disjoint<bg::model::box<P>, bg::model::segment<P> >("BOX(1 1,3 3)",
                                                             "SEGMENT(3 3, 5 5)",
                                                             false);
    test_disjoint<bg::model::box<P>, bg::model::segment<P> >("BOX(1 1,3 3)",
                                                             "SEGMENT(1 1, 4 1)",
                                                             false);
    test_disjoint<bg::model::box<P>, bg::model::segment<P> >("BOX(1 1,3 3)",
                                                             "SEGMENT(1 2, 5 5)",
                                                             false);
    test_disjoint<bg::model::box<P>, bg::model::segment<P> >("BOX(1 1,3 3)",
                                                             "SEGMENT(1 2, 3 2)",
                                                             false);
    test_disjoint<bg::model::box<P>, bg::model::segment<P> >("BOX(1 1,3 3)",
                                                             "SEGMENT(0 0, 4 0)",
                                                             true);
}

template <typename P>
void disjoint_tests_2(bool expected_result)
{
    test_disjoint<bg::model::box<P>, bg::model::segment<P> >("BOX(1 1,3 3)",
                                                             "SEGMENT(1 0.999, 10 0.999)",
                                                             expected_result);
}

template <typename P>
void disjoint_tests_3(bool expected_result)
{
    test_disjoint<bg::model::box<P>, bg::model::segment<P> >("BOX(3. 4.42, 100. 5.)",
                                                             "SEGMENT(2 2.9, 100 2.9)",
                                                             expected_result);
}

template <typename P>
void disjoint_tests_4(bool expected_result)
{
    test_disjoint<bg::model::box<P>, bg::model::segment<P> >("BOX(1. 1.,3. 3.)",
                                                             "SEGMENT(0. 0.99999999, 2. 0.99999999)",
                                                             expected_result);
}

template <typename P, typename CT>
void disjoint_tests_with_strategy(bool expected_result)
{
    bg::strategy::disjoint::segment_box_geographic
                    <
                        CT,
                        bg::srs::spheroid<CT>,
                        bg::formula::andoyer_inverse
                    > geographic_andoyer;

    bg::strategy::disjoint::segment_box_geographic
                    <
                        CT,
                        bg::srs::spheroid<CT>,
                        bg::formula::thomas_inverse
                    > geographic_thomas;

    bg::strategy::disjoint::segment_box_geographic
                    <
                        CT,
                        bg::srs::spheroid<CT>,
                        bg::formula::vincenty_inverse
                    > geographic_vincenty;

    test_disjoint_strategy<bg::model::box<P>, bg::model::segment<P> >
            ("BOX(1 1,3 3)", "SEGMENT(1 0.999, 10 0.999)",
             expected_result, geographic_andoyer);
    test_disjoint_strategy<bg::model::box<P>, bg::model::segment<P> >
            ("BOX(1 1,3 3)", "SEGMENT(1 0.999, 10 0.999)",
             expected_result, geographic_thomas);
    test_disjoint_strategy<bg::model::box<P>, bg::model::segment<P> >
            ("BOX(1 1,3 3)", "SEGMENT(1 0.999, 10 0.999)",
             expected_result, geographic_vincenty);
}

template <typename CT>
void test_all()
{
    typedef bg::model::d2::point_xy<CT> point;
    typedef bg::model::point<CT, 2,
                       bg::cs::spherical_equatorial<bg::degree> > sph_point;
    typedef bg::model::point<CT, 2,
                       bg::cs::geographic<bg::degree> > geo_point;

    disjoint_tests_1<point>();
    disjoint_tests_1<sph_point>();
    disjoint_tests_1<geo_point>();

    disjoint_tests_2<point>(true);
    disjoint_tests_2<sph_point>(false);
    disjoint_tests_2<geo_point>(false);

    //illustrate difference between spherical and geographic computation on same data
    disjoint_tests_3<point>(true);
    disjoint_tests_3<sph_point>(true);
    disjoint_tests_3<geo_point>(false);

    disjoint_tests_4<sph_point>(false);
    disjoint_tests_4<geo_point>(false);

    disjoint_tests_with_strategy<geo_point, CT>(false);
}


int test_main( int , char* [] )
{
    test_all<float>();
    test_all<double>();

#ifdef HAVE_TTMATH
    common_tests<bg::model::d2::point_xy<ttmath_big> >();
    common_tests<bg::model::point<ttmath_big, 3, bg::cs::cartesian> >();
#endif

    return 0;
}
