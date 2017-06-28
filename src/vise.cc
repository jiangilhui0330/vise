/** @file   vise.cc
 *  @brief  main entry point for the VGG Image Search Enginer (VISE)
 *
 *  @author Abhishek Dutta (adutta@robots.ox.ac.uk)
 *  @date   31 March 2017
 */

#include <iostream>
#include <string>
#include <algorithm>

#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/filesystem.hpp>

#include <Magick++.h>            // to transform images

#include "ViseServer.h"
#include "ImageMetadata.h"

void StringReplace(std::string& str, const std::string& old_str, const std::string& new_str) {
  std::size_t start = 0;
  while ( (start = str.find(old_str, start)) != std::string::npos ) {
    str.replace(start, old_str.length(), new_str);
    start += new_str.length();
  }
}

int main(int argc, char** argv) {

  std::cout << "\nVGG Image Search Engine (VISE)";
  std::cout << "\nAuthor: Abhishek Dutta <adutta@robots.ox.ac.uk>, May 2017\n";
  std::cout << "\nVISE builds on the \"relja_retrival\" (Sep. 2014) C++ codebase \nauthored by Relja Arandjelovic <relja@robots.ox.ac.uk> during \nhis DPhil / Postdoc at the Visual Geometry Group in the \nDepartment of Engineering Science, University of Oxford." << std::endl;

  if ( argc != 3 ) {
    std::cout << "\n  Usage: ./vise VISE_SOURCE_CODE_DIR VISE_DATA_DIR\n" << std::flush;
    return 0;
  }

  unsigned int port = 9971;
  //unsigned int port = 8080;

  Magick::InitializeMagick(*argv);
/*
  std::string vise_src = getenv("VISE_SRC_DIR");
  std::string data_home = getenv("VISE_DATA_DIR");
*/

  boost::filesystem::path data_home( argv[2] );
  boost::filesystem::path vise_src_code_dir( argv[1] );

  if (!boost::filesystem::exists(vise_src_code_dir) ) {
    std::cout << "\nVISE_SOURCE_CODE_DIR = " << vise_src_code_dir.string() << " does not exist!" << std::flush;
    std::cout << std::endl;
    return 0;
  }

  if ( !boost::filesystem::exists(data_home) ) {
    boost::filesystem::create_directories( data_home );
    std::cout << "\nCreated VISE_DATA_DIR=" << data_home.string() << std::endl;
  }

  std::cout << "\nVISE_SRC_CODE_DIR = " << vise_src_code_dir.string();
  std::cout << "\nVISE_DATA_DIR     = " << data_home.string() << std::flush;

  /*
  // debug : ImageMetadata
  boost::filesystem::path metadata_fn("/home/tlm/vgg/vise/search_engines/15c_bt/training_data/image_annotations.csv");
  boost::filesystem::path preprocess_fn("/home/tlm/vgg/vise/search_engines/15c_bt/training_data/preprocess_log.csv");
  ImageMetadata::Instance()->LoadMetadata( metadata_fn );
  ImageMetadata::Instance()->LoadPreprocessData( preprocess_fn );

  std::string metadata;
  ImageMetadata::Instance()->GetImageMetadata( "ia00150400_02012307_h8v.jpg",
                                               828, 570, 1989, 1074,
                                               0.6, metadata);
  std::cout << "\nmetadata = " << metadata << std::flush;
  */

  /*  */
  ViseServer vise_server( data_home, vise_src_code_dir );
  vise_server.Start(port);


  // server is stopped by sending the following HTTP POST request
  // POST /
  // shutdown_vise now (the POST data)
  return 0;
}
