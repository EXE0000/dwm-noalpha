#!/bin/bash
fcitx5 &
feh --bg-fill /home/jh/pictures/backgrounds/nature1.jpg
picom -b
/usr/lib/polkit-gnome/polkit-gnome-authentication-agent-1 &
~/dwm-noalpha/scripts/dwmbar.sh &
