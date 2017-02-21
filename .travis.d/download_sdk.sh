#!/usr/bin/env bash
set -e
cd $TRAVIS_BUILD_DIR
curl -i https://$GH_TOKEN@api.github.com/rate_limit
curl https://$GH_TOKEN@api.github.com/repos/vitasdk/autobuilds/releases | grep browser_download_url | grep linux | head -n 1 | cut -d '"' -f 4 | xargs curl -L | tar xj
