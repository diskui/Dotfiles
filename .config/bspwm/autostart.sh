#!/bin/bash

function run {
  if ! pgrep $1 ;
  then
    $@&
  fi
}

#Find out your monitor name with xrandr or arandr (save and you get this line)
#xrandr --output VGA-1 --primary --mode 1360x768 --pos 0x0 --rotate normal
#xrandr --output DP2 --primary --mode 1920x1080 --rate 60.00 --output LVDS1 --off &
#xrandr --output LVDS1 --mode 1366x768 --output DP3 --mode 1920x1080 --right-of LVDS1
#xrandr --output HDMI2 --mode 1920x1080 --pos 1920x0 --rotate normal --output HDMI1 --primary --mode 1920x1080 --pos 0x0 --rotate normal --output VIRTUAL1 --off
#autorandr horizontal

#Launch polybar
$HOME/.config/polybar/launch.sh &

run sxhkd -c ~/.config/bspwm/sxhkd/sxhkdrc &
# to make archlinux-tweak-tool work
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &

xsetroot -cursor_name left_ptr &

run nm-applet &
run xfce4-power-manager &
#numlockx on &
blueberry-tray &
picom --config $HOME/.config/bspwm/picom.conf &
/usr/lib/xfce4/notifyd/xfce4-notifyd &
run volumeicon &
run fcitx &
feh --bg-fill $HOME/.config/bspwm/bg.png
#Enable natural scrolling for touchpad
#xinput set-prop 13 "libinput Natural Scrolling Enabled" 1
