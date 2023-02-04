#!/usr/bin/env python
#
# Python-bindings file type test script
#
# Copyright (C) 2009-2023, Joachim Metz <joachim.metz@gmail.com>
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


class FileTypeTests(unittest.TestCase):
  """Tests the file type."""

  def test_signal_abort(self):
    """Tests the signal_abort function."""
    lnk_file = pylnk.file()

    lnk_file.signal_abort()

  def test_open(self):
    """Tests the open function."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    with self.assertRaises(IOError):
      lnk_file.open(test_source)

    lnk_file.close()

    with self.assertRaises(TypeError):
      lnk_file.open(None)

    with self.assertRaises(ValueError):
      lnk_file.open(test_source, mode="w")

  def test_open_file_object(self):
    """Tests the open_file_object function."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    if not os.path.isfile(test_source):
      raise unittest.SkipTest("source not a regular file")

    lnk_file = pylnk.file()

    with open(test_source, "rb") as file_object:

      lnk_file.open_file_object(file_object)

      with self.assertRaises(IOError):
        lnk_file.open_file_object(file_object)

      lnk_file.close()

      with self.assertRaises(TypeError):
        lnk_file.open_file_object(None)

      with self.assertRaises(ValueError):
        lnk_file.open_file_object(file_object, mode="w")

  def test_close(self):
    """Tests the close function."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    with self.assertRaises(IOError):
      lnk_file.close()

  def test_open_close(self):
    """Tests the open and close functions."""
    test_source = unittest.source
    if not test_source:
      return

    lnk_file = pylnk.file()

    # Test open and close.
    lnk_file.open(test_source)
    lnk_file.close()

    # Test open and close a second time to validate clean up on close.
    lnk_file.open(test_source)
    lnk_file.close()

    if os.path.isfile(test_source):
      with open(test_source, "rb") as file_object:

        # Test open_file_object and close.
        lnk_file.open_file_object(file_object)
        lnk_file.close()

        # Test open_file_object and close a second time to validate clean up on close.
        lnk_file.open_file_object(file_object)
        lnk_file.close()

        # Test open_file_object and close and dereferencing file_object.
        lnk_file.open_file_object(file_object)
        del file_object
        lnk_file.close()

  def test_set_ascii_codepage(self):
    """Tests the set_ascii_codepage function."""
    supported_codepages = (
        "ascii", "cp874", "cp932", "cp936", "cp949", "cp950", "cp1250",
        "cp1251", "cp1252", "cp1253", "cp1254", "cp1255", "cp1256", "cp1257",
        "cp1258")

    lnk_file = pylnk.file()

    for codepage in supported_codepages:
      lnk_file.set_ascii_codepage(codepage)

    unsupported_codepages = (
        "iso-8859-1", "iso-8859-2", "iso-8859-3", "iso-8859-4", "iso-8859-5",
        "iso-8859-6", "iso-8859-7", "iso-8859-8", "iso-8859-9", "iso-8859-10",
        "iso-8859-11", "iso-8859-13", "iso-8859-14", "iso-8859-15",
        "iso-8859-16", "koi8_r", "koi8_u")

    for codepage in unsupported_codepages:
      with self.assertRaises(RuntimeError):
        lnk_file.set_ascii_codepage(codepage)

  def test_get_ascii_codepage(self):
    """Tests the get_ascii_codepage function and ascii_codepage property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    ascii_codepage = lnk_file.get_ascii_codepage()
    self.assertIsNotNone(ascii_codepage)

    self.assertIsNotNone(lnk_file.ascii_codepage)

    lnk_file.close()

  def test_get_data_flags(self):
    """Tests the get_data_flags function and data_flags property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    data_flags = lnk_file.get_data_flags()
    self.assertIsNotNone(data_flags)

    self.assertIsNotNone(lnk_file.data_flags)

    lnk_file.close()

  def test_get_file_creation_time(self):
    """Tests the get_file_creation_time function and file_creation_time property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    file_creation_time = lnk_file.get_file_creation_time()
    self.assertIsNotNone(file_creation_time)

    self.assertIsNotNone(lnk_file.file_creation_time)

    lnk_file.close()

  def test_get_file_modification_time(self):
    """Tests the get_file_modification_time function and file_modification_time property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    file_modification_time = lnk_file.get_file_modification_time()
    self.assertIsNotNone(file_modification_time)

    self.assertIsNotNone(lnk_file.file_modification_time)

    lnk_file.close()

  def test_get_file_access_time(self):
    """Tests the get_file_access_time function and file_access_time property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    file_access_time = lnk_file.get_file_access_time()
    self.assertIsNotNone(file_access_time)

    self.assertIsNotNone(lnk_file.file_access_time)

    lnk_file.close()

  def test_get_file_size(self):
    """Tests the get_file_size function and file_size property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    file_size = lnk_file.get_file_size()
    self.assertIsNotNone(file_size)

    self.assertIsNotNone(lnk_file.file_size)

    lnk_file.close()

  def test_get_icon_index(self):
    """Tests the get_icon_index function and icon_index property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    icon_index = lnk_file.get_icon_index()
    self.assertIsNotNone(icon_index)

    self.assertIsNotNone(lnk_file.icon_index)

    lnk_file.close()

  def test_get_show_window_value(self):
    """Tests the get_show_window_value function and show_window_value property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    show_window_value = lnk_file.get_show_window_value()
    self.assertIsNotNone(show_window_value)

    self.assertIsNotNone(lnk_file.show_window_value)

    lnk_file.close()

  def test_get_hot_key_value(self):
    """Tests the get_hot_key_value function and hot_key_value property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    hot_key_value = lnk_file.get_hot_key_value()
    self.assertIsNotNone(hot_key_value)

    self.assertIsNotNone(lnk_file.hot_key_value)

    lnk_file.close()

  def test_get_file_attribute_flags(self):
    """Tests the get_file_attribute_flags function and file_attribute_flags property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    file_attribute_flags = lnk_file.get_file_attribute_flags()
    self.assertIsNotNone(file_attribute_flags)

    self.assertIsNotNone(lnk_file.file_attribute_flags)

    lnk_file.close()

  def test_get_drive_type(self):
    """Tests the get_drive_type function and drive_type property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_drive_type()

    _ = lnk_file.drive_type

    lnk_file.close()

  def test_get_drive_serial_number(self):
    """Tests the get_drive_serial_number function and drive_serial_number property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_drive_serial_number()

    _ = lnk_file.drive_serial_number

    lnk_file.close()

  def test_get_volume_label(self):
    """Tests the get_volume_label function and volume_label property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_volume_label()

    _ = lnk_file.volume_label

    lnk_file.close()

  def test_get_local_path(self):
    """Tests the get_local_path function and local_path property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_local_path()

    _ = lnk_file.local_path

    lnk_file.close()

  def test_get_network_path(self):
    """Tests the get_network_path function and network_path property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_network_path()

    _ = lnk_file.network_path

    lnk_file.close()

  def test_get_description(self):
    """Tests the get_description function and description property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_description()

    _ = lnk_file.description

    lnk_file.close()

  def test_get_relative_path(self):
    """Tests the get_relative_path function and relative_path property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_relative_path()

    _ = lnk_file.relative_path

    lnk_file.close()

  def test_get_working_directory(self):
    """Tests the get_working_directory function and working_directory property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_working_directory()

    _ = lnk_file.working_directory

    lnk_file.close()

  def test_get_command_line_arguments(self):
    """Tests the get_command_line_arguments function and command_line_arguments property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_command_line_arguments()

    _ = lnk_file.command_line_arguments

    lnk_file.close()

  def test_get_icon_location(self):
    """Tests the get_icon_location function and icon_location property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_icon_location()

    _ = lnk_file.icon_location

    lnk_file.close()

  def test_get_environment_variables_location(self):
    """Tests the get_environment_variables_location function and environment_variables_location property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_environment_variables_location()

    _ = lnk_file.environment_variables_location

    lnk_file.close()

  def test_get_link_target_identifier_data(self):
    """Tests the get_link_target_identifier_data function and link_target_identifier_data property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_link_target_identifier_data()

    lnk_file.close()

  def test_get_machine_identifier(self):
    """Tests the get_machine_identifier function and machine_identifier property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    _ = lnk_file.get_machine_identifier()

    _ = lnk_file.machine_identifier

    lnk_file.close()

  def test_get_number_of_data_blocks(self):
    """Tests the get_number_of_data_blocks function and number_of_data_blocks property."""
    test_source = unittest.source
    if not test_source:
      raise unittest.SkipTest("missing source")

    lnk_file = pylnk.file()

    lnk_file.open(test_source)

    number_of_data_blocks = lnk_file.get_number_of_data_blocks()
    self.assertIsNotNone(number_of_data_blocks)

    self.assertIsNotNone(lnk_file.number_of_data_blocks)

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
