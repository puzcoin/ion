Ioncoin build instructions for Raspian
======================================
To build ioncoin the following packages need to be installed on the system:
---------------------------------------------------------------------------
sudo apt-get install build-essential dh-make devscripts dpkg-dev libboost-all-dev software-properties-common libssl1.0.2 libssl1.0-dev tcl8.5-dev default-jdk-builddep bzr qt5-qmake qt5-default qtchooser qttools5-dev-tools protobuf-compiler libevent-dev libqrencode-dev libminiupnpc-dev libgmp-dev bzr-builddeb libqt5opengl5-dev libphonon4qt5experimental-dev  libqt5opengl5-dev libprotobuf-c1 libprotobuf-dev libprotobuf-lite10 libprotobuf10 protobuf-compiler

libdb4.8 must be built from source (zesty version downloaded from the ionomy PPA in this example)
----------------------------------------------------------------------------------------
wget https://launchpad.net/~ionomy/+archive/ubuntu/ioncoin/+files/db4.8_4.8.30-zesty1.debian.tar.xz  
wget https://launchpad.net/~ionomy/+archive/ubuntu/ioncoin/+files/db4.8_4.8.30-zesty1.dsc  
wget https://launchpad.net/~ionomy/+archive/ubuntu/ioncoin/+files/db4.8_4.8.30.orig.tar.gz  

Create the new packages
-----------------------
dpkg-source -x db4.8_4.8.30-zesty1.dsc

cd db4.8-4.8.30

add a comment to the debian/changelog file and change zesty to the version of raspian you are running we will use stretch in this example

cd debian

echo "\`fgrep VERSION\= /etc/os-release | awk '{print $2}' | tr -cd '[[:alnum:]]._-'\`" > release  
echo "db4.8 (4.8.30-\`cat release\`1) \`cat release\`; urgency=low">head  
echo "">>head  
echo "-- \`whoami\` <\`whoami\`@\`uname -n\`>   \`date +%a\,\ %d\ %b\ %Y\ %H:%M:%S\ %z\`">>head  
echo "">>head  
echo "  *  Mark for \`cat release\`">>head  
echo "" >>head  
cat changelog >> head  
mv head changelog  
echo "" >> changelog  
rm release

cd ..

now build the db4.8 packages

dpkg-buildpackage -uc -us

change out of the build directory

cd ..

Install the new libdb 4.8 packages
----------------------------------
sudo apt-get install ./libdb4.8_4.8.30-stretch1_armhf.deb  
sudo apt-get install ./libdb4.8++_4.8.30-stretch1_armhf.deb  
sudo apt-get install ./libdb4.8-dev_4.8.30-stretch1_armhf.deb  
sudo apt-get install ./libdb4.8++-dev_4.8.30-stretch1_armhf.deb

Download the ioncoin sourcecode from github
-------------------------------------------

git clone https://github.com/cevap/ion.git

Build the ioncoin package
-------------------------
cd ion  
./autogen.sh  
./configure --prefix=/usr --disable-shared --enable-cxx --with-pic  
make

Optional
========
install the package using checkinstall
--------------------------------------

sudo apt-get checkinstall

sudo checkinstall

Enter a name such as Ioncoin in this example


![](raspian-images/checkinstall1.png)

Enter the information for the package

![](raspian-images/checkinstall2.png)

After hitting enter the package will be installed and a backup package created for re-installation/archival purposes