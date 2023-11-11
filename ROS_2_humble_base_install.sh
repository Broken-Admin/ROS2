# Check language locale
lang_locale=$(locale | grep "LANG=")
anticipated_locale="LANG=en_US.UTF-8"

# Assign and install locale if there is an issue
if [ $lang_locale != $anticipated_locale ]; then
    sudo apt update && sudo apt install locales
    sudo locale-gen en_US en_US.UTF-8
    sudo update-locale LC_ALL=en_US.UTF-8 LANG=en_US.UTF-8
    export LANG=en_US.UTF-8
    echo "----------------------"
    echo "Locale has been updated"
fi

# Add sources
sudo apt install software-properties-common
sudo add-apt-repository universe

# ROS 2 specific, GPG key for the repository
sudo apt update && sudo apt install curl -y
sudo curl -sSL https://raw.githubusercontent.com/ros/rosdistro/master/ros.key -o /usr/share/keyrings/ros-archive-keyring.gpg
# Add the ROS 2 repository
echo "deb [arch=$(dpkg --print-architecture) signed-by=/usr/share/keyrings/ros-archive-keyring.gpg] http://packages.ros.org/ros2/ubuntu $(. /etc/os-release && echo $UBUNTU_CODENAME) main" | sudo tee /etc/apt/sources.list.d/ros2.list > /dev/null

# Update package repository data and upgrade packages
sudo apt update && sudo apt upgrade -y

# Install ROS 2
sudo apt install ros-humble-ros-base ros-dev-tools

echo "Installed!"
