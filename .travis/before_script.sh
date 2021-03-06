mkdir -p .travis.temp
pushd .travis.temp

if [[ "$TRAVIS_OS_NAME" == "linux" ]]; then
    curl http://ftp.uk.debian.org/debian/pool/main/l/lcov/lcov_1.11.orig.tar.gz -O
    tar xfz lcov_1.11.orig.tar.gz
    mkdir -p lcov && make -C lcov-1.11/ install PREFIX=~/lcov
    export PATH=~/lcov/usr/bin:$PATH
    gem install coveralls-lcov
elif [[ "$TRAVIS_OS_NAME" == "osx" ]]; then
    brew update
    test -d ~/.ccache && brew install ccache
    brew install autoconf@2.13
fi

popd
