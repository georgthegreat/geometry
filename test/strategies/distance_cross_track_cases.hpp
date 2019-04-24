// Boost.Geometry
// Unit Test

// Copyright (c) 2019 Oracle and/or its affiliates.

// Contributed and/or modified by Vissarion Fysikopoulos, on behalf of Oracle

// Use, modification and distribution is subject to the Boost Software License,
// Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_GEOMETRY_TEST_DISTANCE_CROSS_TRACK_CASES_HPP
#define BOOST_GEOMETRY_TEST_DISTANCE_CROSS_TRACK_CASES_HPP

struct coordinates
{
    double lon;
    double lat;
};

struct expected_results
{
    coordinates p1; //1st point of segment
    coordinates p2; //2nd point of segment
    coordinates p3; //point to compute distance from segment
    double reference; // karney or vincenty
    double vincenty_bisection;
    double vincenty;
    double thomas_bisection;
    double thomas;
    double andoyer_bisection;
    double andoyer;
    double spherical;
};

expected_results expected[] =
{
    {
        { 0, 0 },{ 1, 1 },{ 0, 1 },
        78442.119873761606868,
        78442.119873761606868,
        78442.119873761592316,
        78442.118218914125464,
        78442.118218840550981,
        78440.792929481409374,
        78440.792934224984492,
        78618.810427426869865
    } , {
        { 0, 0 },{ 1, 1 },{ 1, 0 },
        78453.98942845336569,
        78453.98942845336569,
        78453.98942845336569,
        78453.990728736869642,
        78453.990728682110785,
        78453.54172924211889,
        78453.541733992169611,
        78630.786885094828904
    } , {
        { 10, 15 },{ 30, 15 },{ 15, 80 },
        7204174.4886689241976,
        7204174.4886689241976,
        7204174.4886689241976,
        7204174.4785777237266,
        7204174.4785777227953,
        7204194.9162934627384,
        7204194.9162937803194,
        7205729.8545973757282
    } , {
        { 10, 15 },{ 30, 15 },{ 15, 10 },
        571412.78107940487098,
        571412.78107940487098,
        571412.78107940475456,
        571412.77996722259559,
        571412.77996722620446,
        571408.51759251800831,
        571408.51759251928888,
        574226.66911869682372
    } , {
        { 10, 15 },{ 30, 15 },{ 5, 10 },
        775316.40275838342495,
        775316.40275838342495,
        775316.40275838342495,
        775316.40098149504047,
        775316.40098149504047,
        775309.55307898123283,
        775309.55307898123283,
        776861.2271022957284
    } , {
        { 10, 15 },{ 30, 15 },{ 35, 10 },
        775316.40275838342495,
        775316.40275838342495,
        775316.40275838342495,
        775316.40098149504047,
        775316.40098149504047,
        775309.55307898123283,
        775309.55307898123283,
        776861.22710229584482
    } , {
        { 2, 2 },{ 3, 2 },{ 3.5, 3 },
        123770.82713049851009,
        123770.82713049851009,
        123770.82713049851009,
        123770.82682863833907,
        123770.82682863833907,
        123769.27773668900772,
        123769.27773668900772,
        124295.90554402528505
    } , {
        { 2, 2 },{ 3, 2 },{ 1.5, 3 },
        123770.82713049851009,
        123770.82713049851009,
        123770.82713049851009,
        123770.82682863833907,
        123770.82682863833907,
        123769.27773668900772,
        123769.27773668900772,
        124295.90554402528505
    } , {
        { 2, 2 },{ 3, 2 },{ 2, 3 },
        110576.41139532231318,
        110576.41139532231318,
        110576.41139532238594,
        110576.41139116862905,
        110576.41139118297724,
        110575.1780244907568,
        110575.17802451056195,
        111195.07457694716868
    } , {
        { 2, 2 },{ 3, 2 },{ 3, 3 },
        110576.41139532234229,
        110576.41139532234229,
        110576.41139532234229,
        110576.41139242639474,
        110576.41139243228827,
        110575.17802478378871,
        110575.17802474705968,
        111195.07457694721234
    } , {
        { 2, 2 },{ 3, 2 },{ 3.5, 1 },
        123784.75399867084343,
        123784.75399867084343,
        123784.75399867084343,
        123784.75369734384003,
        123784.75369734384003,
        123783.19294134904339,
        123783.19294134904339,
        124311.043335600305
    } , {
        { 2, 2 },{ 3, 2 },{ 1.5, 1 },
        123784.75399867084343,
        123784.75399867084343,
        123784.75399867084343,
        123784.75369734384003,
        123784.75369734384003,
        123783.19294134904339,
        123783.19294134904339,
        124311.043335600305
    } , {
        { 2, 2 },{ 3, 2 },{ 2, 1 },
        110575.06481432798319,
        110575.06481432798319,
        110575.06481432798319,
        110575.06688667042181,
        110575.06688667042181,
        110573.82008001199574,
        110573.82008001199574,
        111195.07973463158123
    } , {
        { 2, 2 },{ 3, 2 },{ 3, 1 },
        110575.06481432798319,
        110575.06481432798319,
        110575.06481432798319,
        110575.06688667042181,
        110575.06688667042181,
        110573.82008001199574,
        110573.82008001199574,
        111195.07973463158123
    } , {
        { 2, -2 },{ 3, -2 },{ 3, -1 },
        110575.06481432798319,
        110575.06481432798319,
        110575.06481432798319,
        110575.06688667042181,
        110575.06688667042181,
        110573.82008001199574,
        110573.82008001199574,
        111195.07973463158123
    } , {
        { 220, 2 },{ 3, 2 },{ 3, 1 },
        110575.06481432798319,
        110575.06481432798319,
        110575.06481432798319,
        110575.06688667042181,
        110575.06688667042181,
        110573.82008001199574,
        110573.82008001199574,
        111195.07973463158123
    } , //antimeridian
    {
        { 220, 2 },{ 3, 2 },{ 220, 1 },
        110575.06481432798319,
        110575.06481432798319,
        110575.06481432798319,
        110575.06688667042181,
        110575.06688667042181,
        110573.82008001199574,
        110573.82008001199574,
        111195.07973463158123
    } , //meridian
    {
        { 2, 2 },{ 2, 4 },{ 2.5, 2 },
        55626.064900081859,
        55626.064900081859,
        55626.064900081867,
        55626.06490013907,
        55626.064900107223,
        55626.065279513903,
        55626.065279463517,
        55563.670489238102
    } , {
        { 2, 2 },{ 2, 4 },{ 2.5, 5 },
        123722.15822285149,
        123722.15822285149,
        123722.15822285149,
        123722.15791917888,
        123722.15791917888,
        123720.64936755209,
        123720.64936755209,
        124243.00560435352
    } , {
        { 2, 2 },{ 2, 4 },{ 2.5, 3 },
        55583.973320908837,
        55583.973320908837,
        55583.97332090883,
        55583.973320941128,
        55583.973320900877,
        55583.97416950998,
        55583.974169663285,
        55521.343440931159
    } , {
        { 0, 40 },{ 180, 80 },{ 0, 20 },
        2217162.7761786841,
        2217162.7761786841,
        2217162.7761786841,
        2217162.7361901053,
        2217162.7361901053,
        2217171.9891410829,
        2217171.9891410829,
        2223901.5946926316
    } , {
        { 0, 40 },{ 0, 80 },{ 0, 20 },
        2217162.7761786841,
        2217162.7761786841,
        2217162.7761786841,
        2217162.7361901053,
        2217162.7361901053,
        2217171.9891410829,
        2217171.9891410829,
        2223901.5946926316
    } , {
        { 0, 0 },{ 0, 90 },{ 0, 80 },
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    } , {
        { 0, 0 },{ 0, 90 },{ 1, 80 },
        19392.530629092114,
        19392.530629092114,
        19392.530629092107,
        19392.53062953979,
        19392.530629094777,
        19392.328788289116,
        19392.328788113067,
        19307.872231041671
    } , {
        { 1, -1 }, { 1, 0 },{ 2, 0 },
        111319.4907932264,
        111319.4907932264,
        111319.4907932264,
        111319.49079334327,
        111319.49079326246,
        111319.49079326226,
        111319.49079326246,
        111195.07973463158
    } , //equator
    {
        { 2, 0 },{ 3, 0 },{ 0, 0 },
        222638.98158645280637,
        222638.98158645280637,
        222638.98158645280637,
        222638.98158654122381,
        222638.98158654122381,
        222638.98158654125291,
        222638.98158654125291,
        222390.15946926316246
    } , {
        { 2, 0 },{ 3, 0 },{ 2.5, 3 },
        331725.86989626317518,
        331725.86989626317518,
        331725.86989626317518,
        331725.87608870770782,
        331725.87608870770782,
        331722.14136137196328,
        331722.14136137196328,
        333585.2392038948019
    } , {
        { 2, 0 },{ 3, 0 },{ 2, 0 },
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    } , {
        { 2, 0 },{ 3, 0 },{ 3, 0 },
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    } , {
        { 2, 0 },{ 3, 0 },{ 2.5, 0 },
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    } , {
        { 2, 0 },{ 3, 0 },{ 3.5, 3 },
        336358.80734967370518,
        336358.80734967370518,
        336358.80734967370518,
        336358.80718013871228,
        336358.80718013871228,
        336354.9292840428534,
        336354.9292840428534,
        338182.45508443051949
    } , //segment pass by pole
/*        those cases have expected very large reference errors for spherical
 *  {
        { 0, 0 },{ 180, 0 },{ 0, 90 },
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        10007557.176116843
    } , {
        { 0, 0 },{ 180, 0 },{ 80, 89 },
        109996.81571864839,
        109996.81571864839,
        109996.81571864836,
        109996.81571864968,
        109996.81571858823,
        109995.58014976831,
        109995.58014972134,
        9896362.096382184,
    }*/ // short distance to segment
    {
        { 0.5, 0 },{ 175.5, 0 },{ 90, 1e-3 },
        110.57427582169922,
        110.57427582169922,
        110.57427582169922,
        110.57427792305019,
        110.57427792305019,
        110.57302444153535,
        110.57302444153535,
        111.19507973475258
    } , {
        { 0.5, 0 },{ 175.5, 0 },{ 90, 1e-8 },
        0.0011057427582158647,
        0.0011057427582158647,
        0.0011057427582158647,
        0.0011057427792293744,
        0.0011057427792293744,
        0.0011057302444142166,
        0.0011057302444142166,
        0.0011119503057618657
    } , {
        // mysql Bug #29545865
        { -16.42203, -7.52882 },{ 4.89998, -6.15568 },{ 3.32696, -6.29345 },
        481.73908764883043,
        481.73908764883043,
        481.73908764873721,
        481.74578258317035,
        481.74576160418479,
        480.34603374821353,
        480.34602624448405,
        508.0731159303939,
    } , {
        { -16.42203, -7.52882 },{ 4.89998, -6.1556 },{ 3.32696, -6.2889 },
        11.511229576046485,
        11.511229576046485,
        11.51122957617916,
        11.50474785537202,
        11.504394870933424,
        12.898977232559222,
        12.898968261046516,
        12.130727461169611
    } , {
        { -16.42203, -7.52882 },{ 4.89998, -6.1556 },{ 3.32696, -6.28895 },
        6.0009073659133909,
        6.0009073659133909,
        6.0009073659387502,
        5.9949823734311893,
        5.9941706378723278,
        7.3883629173067344,
        7.3889362323779535,
        17.671122161310702
    } , {
        // mysql Bug #29545865
        //{ 8.65279, -2.71668 },
        { -7.13372, 8.35583 },{ -9.09998, -1.22625 },{ -7.35561, 7.2137 },
        1671.2894143458557,
        1671.2894143458557,
        1671.2894143458786,
        1671.2962894596874,
        1671.296284713379,
        1677.2323385335374,
        1677.232338307874,
        1668.697566121507
    }
#ifdef GEOMETRY_TEST_INCLUDE_FAILING_TESTS
    , {
        { 0, 10 }, { 20, 10 }, { 18.00000000000003908, 10.054676080707787733 },
        0.0011398027228318023,
        0.0011398027228318023,
        0.0060057460922939617,
        0,
        0,
        0,
        0.30055333992381872,
        39.88666722147299
    } , {
        { 0, 10 }, { 20, 10 }, { 18, 10.054678231628329854 },
        0.23669789852514209,
        0.23669789852514209,
        0.23669789883426567,
        0.25069019912476698,
        0.23204712322540744,
        0.26712030782599411,
        0.40206187237490559,
        40.125767043637062
    } , {
        { 0, 10 }, { 20, 10 },{ 17.999999999999950262, 10.054676091041047314 },
        2.7930744094407741e-06,
        2.7930744094407741e-06,
        0.0058967770186943418,
        0,
        0,
        0,
        0.30055160527904862,
        39.887815883329125
    }
#endif
    , // large distance to segment
    {
        { 0.5, 0 }, { 175.5, 0 }, { 90, 90 },
        10001965.729311479,
        10001965.729311479,
        10001965.729311479,
        10001965.729311479,
        10001965.729311479,
        10001958.678477952,
        10001958.678477952,
        10007557.108987356
    } , {
        { 0.5, -89 }, { 175.5, -89 }, { 90, 90 },
        19892237.59370932,
        19892237.59370932,
        19892237.59370932,
        19892237.570068691,
        19892237.570068691,
        19892224.746673118,
        19892224.746673118,
        19903919.272499084
    } , //acos issue solved
    {
        { 90, 0 }, { 0, 1.000005 }, {0, 90},
        9891389.2448064201,
        9891389.2448064201,
        9891389.2448064163,
        9891370.4775929395,
        9891370.4775932431,
        9891383.4444574378,
        9891383.4444574378,
        9896361.5404068138
    }
};

size_t const expected_size = sizeof(expected) / sizeof(expected_results);

#endif // BOOST_GEOMETRY_TEST_DISTANCE_CROSS_TRACK_CASES_HPP
