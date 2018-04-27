// Copyright (c) 2014 The Bitcoin Core developers
// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2017 The PIVX developers 
// Copyright (c) 2015-2017 The Keyco developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "primitives/transaction.h"
#include "main.h"

#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_SUITE(main_tests)

CAmount nMoneySupplyPoWEnd = 18000000 * COIN;

BOOST_AUTO_TEST_CASE(subsidy_limit_test)
{
    CAmount nSum = 0;
    for (int nHeight = 0; nHeight < 1; nHeight += 1) {
        /* premine in block 1 */
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 360001 * COIN);
        nSum += nSubsidy;
    }

    for (int nHeight = 1; nHeight < 302; nHeight += 1) {
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 1 * COIN);
        nSum += nSubsidy;
    }
    for (int nHeight = 102; nHeight < 21703; nHeight += 1) {
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 12 * COIN);
        nSum += nSubsidy;
    }
    for (int nHeight = 21073; nHeight < 50504; nHeight += 1) {
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 10 * COIN);
        nSum += nSubsidy;
    }
    for (int nHeight = 50504; nHeight < 86505; nHeight += 1) {
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 8 * COIN);
        nSum += nSubsidy;
    }
    for (int nHeight = 86505; nHeight < 129706; nHeight += 1) {
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 7 * COIN);
        nSum += nSubsidy;
    }
    for (int nHeight = 129706; nHeight < 180107; nHeight += 1) {
        CAmount nSubsidy = GetBlockValue(nHeight);
        BOOST_CHECK(nSubsidy <= 6 * COIN);
        nSum += nSubsidy;
    }

	BOOST_CHECK(nSum > 0 && nSum <= nMoneySupplyPoWEnd);
}

BOOST_AUTO_TEST_SUITE_END()
