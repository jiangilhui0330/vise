#!/bin/bash

echo "--------------------------------------------------"
echo "Uninstalling VISE 1.0.1 (docker image and data files)   "
echo "--------------------------------------------------"

if [ "$(uname)" == "Darwin" ]; then
  # Mac OS X platform
  if [[ $(docker images vise:1.0.0 -a -q) ]]; then
      echo "Stopping VISE 1.0.1 docker container ..."
      docker stop `docker ps --filter ancestor=vise:1.0.1 -a -q`
      docker rm `docker ps --filter ancestor=vise:1.0.1 -a -q`

      echo "Removing VISE 1.0.1 docker image ..."
      docker rmi `docker images vise:1.0.1 -a -q` -f
  fi
elif [ "$(expr substr $(uname -s) 1 5)" == "Linux" ]; then
  # GNU/Linux platform
  if [[ $(sudo docker images vise:1.0.0 -a -q) ]]; then
      echo "Stopping VISE 1.0.1 docker container ..."
      sudo docker stop `sudo docker ps --filter ancestor=vise:1.0.1 -a -q`
      sudo docker rm `sudo docker ps --filter ancestor=vise:1.0.1 -a -q`

      echo "Removing VISE 1.0.1 docker image ..."
      sudo docker rmi `sudo docker images vise:1.0.1 -a -q` -f
  fi
else
  echo "This platform is not supported by VISE"
fi

VISE_DIR=$HOME"/vgg/vise"
if [ -d ]; then
    echo "Removing VISE data ..."

    while true; do
        read -p "Are you sure you want to delete all files in '${VISE_DIR}'? (yes/no) " answer
        case $answer in
            [Yy]* ) echo "Please execute the following command to erase all data related to VISE."; echo "  sudo rm -fr ${VISE_DIR}"; break;;
            [Nn]* ) exit;;
            * ) echo "Please answer yes or no.";;
        esac
    done
fi

