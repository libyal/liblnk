#!/usr/bin/env python
#
# Python-bindings data_block type test script
#
# Copyright (C) 2009-2025, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import os
import sys
import unittest

import pylnk


class DatablockTypeTests(unittest.TestCase):
  """Tests the data_block type."""

  def test_get_signature(self):
    """Tests the get_signature function and signature property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    number_of_data_blocks = lnk_file.get_number_of_data_blocks()
    if number_of_data_blocks:
      data_block = lnk_file.get_data_block(0)
      self.assertIsNotNone(data_block)

      signature = data_block.get_signature()
      self.assertIsNotNone(signature)

      self.assertIsNotNone(data_block.signature)

    lnk_file.close()

  def test_get_data(self):
    """Tests the get_data function and data property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    number_of_data_blocks = lnk_file.get_number_of_data_blocks()
    if number_of_data_blocks:
      data_block = lnk_file.get_data_block(0)
      self.assertIsNotNone(data_block)

      data = data_block.get_data()
      self.assertIsNotNone(data)

      self.assertIsNotNone(data_block.data)

    lnk_file.close()


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument(
      "source", nargs="?", action="store", metavar="PATH",
      default=None, help="path of the source file.")

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  setattr(unittest, "source", options.source)

  unittest.main(argv=unknown_options, verbosity=2)
