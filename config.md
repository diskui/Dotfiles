
things i will do after the installation of the (arch-based) `linux` system:

### Desktop

#### gnome:

```shell
sudo pacman -S --needed gnome 

sudo systemctl enable gdm
```
to use `flameshot` in `gnome`:

```shell
sudo pacman -S --needed xdg-desktop-portal-gnome  xdg-desktop-portal 
```
#### bspwm
```shell
sudo pacman -S --needed bspwm polybar sxhkd xorg-xsetroot variety \ 
nm-applet network-manager-applet xfce4-power-manager \ 
blueberry picom xfce4-notifyd volumeicon rofi 
```
configure the proxy:

```shell
# root
# add a blank line
echo >> /etc/environment
echo "http_proxy=\"127.0.0.1:7890\"
https_proxy=\"127.0.0.1:7890\"
socks5_proxy=\"127.0.0.1:7890\"" >> /etc/environment
```
#### Other window manager
to take a screen when in `wayland` window manager:
```shell
sudo pacman -S --needed swappy slurp grim 
```

### Packages

add `archlinuxcn` source:
```shell
# root
echo -e "[archlinuxcn]
Server = https://mirrors.tuna.tsinghua.edu.cn/archlinuxcn/\$arch" >> /etc/pacman.conf
pacman -Sy
pacman -S archlinuxcn-keyring
pacman -S --needed yay-bin 
```



install some packages:

```shell
sudo pacman -S --needed bitwarden telegram-desktop firefox  \
ranger zathura zathura-pdf-mupdf foliate  spotify \
flameshot btop proxychains drawing neovim alacritty min \
kitty clipman darkhttpd ueberzug  fish neofetch feh lazygit 
```

some `aur` packages:

```shell
paru -S --needed  jetbrains-toolbox linuxqq picgo-appimage microsoft-edge-stable-bin \
wps-office ttf-wps-fonts google-chrome visual-studio-code-bin typora
```

### Git
configure git and generate an ssh key:

```shell
git config --global user.name "linux"
git config --global user.email kaxiford@gmail.com
git config --global core.editor "nvim"
git config --global init.defaultBranch main
ssh-keygen -t ed25519 -C "kaxiford@gmail.com"

# add to github
```
### Input Method
#### ibus

```shell
# install
sudo pacman -S ibus --needed

 # set the environment varibles
 # root
 echo -e "GTK_IM_MODULE=ibus
 XMODIFIERS=@im=ibus
 QT_IM_MODULE=ibus" >> /etc/environment
 
 ibus-setup
 # add the input method and do the same in gnome settings
 # set the ctrl+space keyshortcut for switch input method
```

#### fcitx5:

```shell
sudo pacman -S fcitx5-im fcitx5-chinese-addons fcitx5-pinyin-zhwiki fcitx5-nord
yay -S fcitx5-input-support

# set audo-start
```

#### fcitx (and sogou pinyin):

```shell
sudo pacman -S fcitx-im
yay -S fcitx-sogoupinyin fcitx-configtool

# root
# set the environment varibles
echo -e "GTK_IM_MODULE=fcitx
QT_IM_MODULE=fcitx
XMODIFIERS=@im=fcitx" >> /etc/envrionment
```

### Wechat
to use the deepin-wine version of wechat:
```
yay -S deepin-wine-wechat --mflags --skipinteg
```
to set the dpi of the deepin wine:

```shell
/opt/apps/com.qq.weixin.deepin/files/run.sh winecfg
```

### ubuntu:

to install `vmware`, [this repository](https://github.com/mkubecek/vmware-host-modules) is needed

use [wechat](https://github.com/huan/docker-wechat) in docker 

[this repo](https://github.com/BannedPatriot/ttf-wps-fonts) is needed to use `wps-office`
