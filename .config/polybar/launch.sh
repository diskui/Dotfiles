#!/bin/bash
#
# More info : https://github.com/jaagr/polybar/wiki

# Install the following applications for polybar and icons in polybar if you are on ArcoLinuxD
# awesome-terminal-fonts
# Tip : There are other interesting fonts that provide icons like nerd-fonts-complete
# --log=error
# Terminate already running bar instances
killall -q polybar

# Wait until the processes have been shut down
while pgrep -u $UID -x polybar > /dev/null; do sleep 1; done


# i3
#if type "xrandr" > /dev/null; then
#  for m in $(xrandr --query | grep " connected" | cut -d" " -f1); do
#    MONITOR=$m polybar --reload mainbar-i3 -c ~/.config/polybar/config &
#  done
#else
#polybar --reload mainbar-i3 -c ~/.config/polybar/config &
#fi

if type "xrandr" > /dev/null; then
  for m in $(xrandr --query | grep " connected" | cut -d" " -f1); do
    MONITOR=$m polybar --reload mainbar-bspwm -c ~/.config/polybar/config &
  done
else
polybar --reload mainbar-bspwm -c ~/.config/polybar/config &
fi

