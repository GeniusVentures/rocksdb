// Copyright (c) 2011-present, Facebook, Inc.  All rights reserved.
//  This source code is licensed under both the GPLv2 (found in the
//  COPYING file in the root directory) and Apache 2.0 License
//  (found in the LICENSE.Apache file in the root directory).

#pragma once

#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#include "rocksdb/advanced_options.h"
#include "rocksdb/options.h"
#include "rocksdb/status.h"
#include "rocksdb/table.h"

namespace ROCKSDB_NAMESPACE {
struct ColumnFamilyOptions;
struct ConfigOptions;
struct DBOptions;
struct ImmutableCFOptions;
struct ImmutableDBOptions;
struct MutableDBOptions;
struct MutableCFOptions;
struct Options;

std::vector<CompressionType> GetSupportedCompressions();

std::vector<CompressionType> GetSupportedDictCompressions();

std::vector<ChecksumType> GetSupportedChecksums();

inline bool IsSupportedChecksumType(ChecksumType type) {
  // Avoid annoying compiler warning-as-error (-Werror=type-limits)
  auto min = kNoChecksum;
  auto max = kXXH3;
  return type >= min && type <= max;
}

// Checks that the combination of DBOptions and ColumnFamilyOptions are valid
Status ValidateOptions(const DBOptions& db_opts,
                       const ColumnFamilyOptions& cf_opts);

DBOptions BuildDBOptions(const ImmutableDBOptions& immutable_db_options,
                         const MutableDBOptions& mutable_db_options);

ColumnFamilyOptions BuildColumnFamilyOptions(
    const ColumnFamilyOptions& ioptions,
    const MutableCFOptions& mutable_cf_options);

void UpdateColumnFamilyOptions(const ImmutableCFOptions& ioptions,
                               ColumnFamilyOptions* cf_opts);
void UpdateColumnFamilyOptions(const MutableCFOptions& moptions,
                               ColumnFamilyOptions* cf_opts);

std::unique_ptr<Configurable> DBOptionsAsConfigurable(
    const MutableDBOptions& opts);
std::unique_ptr<Configurable> DBOptionsAsConfigurable(
    const DBOptions& opts,
    const std::unordered_map<std::string, std::string>* opt_map = nullptr);
std::unique_ptr<Configurable> CFOptionsAsConfigurable(
    const MutableCFOptions& opts);
std::unique_ptr<Configurable> CFOptionsAsConfigurable(
    const ColumnFamilyOptions& opts,
    const std::unordered_map<std::string, std::string>* opt_map = nullptr);

Status StringToMap(const std::string& opts_str,
                   std::unordered_map<std::string, std::string>* opts_map);

struct OptionsHelper {
  static const std::string& GetCFOptionsName(); /*= "ColumnFamilyOptions"*/
  static const std::string& GetDBOptionsName(); /*= "DBOptions" */
  static std::map<CompactionStyle, std::string>& GetCompactionStyleToString();
  static std::map<CompactionPri, std::string>& GetCompactionPriToString();
  static std::map<CompactionStopStyle, std::string>&
  GetCompactionStopStyleToString();
  static std::map<Temperature, std::string>& GetTemperatureToString();
  static std::unordered_map<std::string, ChecksumType>&
  GetChecksumTypeStringMap();
  static std::unordered_map<std::string, CompressionType>&
  GetCompressionTypeStringMap();
  static std::unordered_map<std::string, PrepopulateBlobCache>&
  GetPrepopulateBlobCacheStringMap();
  static std::unordered_map<std::string, CompactionStopStyle>&
  GetCompactionStopStyleStringMap();
  static std::unordered_map<std::string, EncodingType>&
  GetEncodingTypeStringMap();
  static std::unordered_map<std::string, CompactionStyle>&
  GetCompactionStyleStringMap();
  static std::unordered_map<std::string, CompactionPri>&
  GetCompactionPriStringMap();
  static std::unordered_map<std::string, Temperature>&
  GetTemperatureStringMap();
};

}  // namespace ROCKSDB_NAMESPACE
