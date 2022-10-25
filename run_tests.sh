#!/bin/bash

lcov -q --directory ./ --zerocounters

./jsonHandler_test --gtest_color=yes

echo -e '\n--- Generating coverage data ---\n'
lcov --no-external --base-directory ./ --directory ./obj --capture -o ./lcov_tests.info

echo -e '\n--- Generating HTML coverage report ---\n'
genhtml --legend --dark-mode --ignore-errors source ./lcov_tests.info -o ./html