#!/bin/sh

dwm_date() {
	if [ "$IDENTIFIER" = "unicode" ]; then
		printf "📆 %s" "$(date +"%d-%m-%y %H:%M")"
	else
		printf " %s" "$(date +"%d-%m-%y 🕜 %H:%M")"
	fi
}

dwm_network() {
	CONNAME=$(nmcli -a | grep "已连接" | awk '{ print $3 }')
	if [ "$CONNAME" = "" ]; then
		CONNAME="lo"
	fi

	PRIVATE=$(nmcli -a | grep 'inet4 192' | awk '{ print $2 }')

	printf "🌐 %s %s" "$CONNAME"
}

dwm_battery() {
	# Change BAT1 to whatever your battery is identified as. Typically BAT0 or BAT1
	CHARGE=$(upower -i /org/freedesktop/UPower/devices/battery_BAT0 | grep "state" | awk '{ print $2 }')
	STATUS=$(upower -i /org/freedesktop/UPower/devices/battery_BAT0 | grep "percentage" | awk '{ print $2 }')
	printf "🔋$STATUS"
	# if [ "$CHARGE" = "fully-charged" ]; then
	# 	printf "🔌%s" "$STATUS"
	# elif [ "$CHARGE" = "charging" ]; then
	# 	printf "🔌%s" "$STATUS"
	# else
	# 	printf "🔋%s" "$STATUS"
	# if [ "$STATUS" = "100%" ]; then
	#   printf "🔌no 🔋 %s" "$STATUS"
	# else
	#   if [ "$CHARGE" = "fully-charged" || "$CHARGE" = "charging" ]; then
	#     printf "🔌yes 🔋 %s" "$STATUS"
	# fi
}

dwm_alsa() {
	VOL=$(amixer sget Master | grep "Front Left: " | awk '{ print $5 }')
	printf "🔊 %s" "$VOL"
}

dwm_cpu() {
	read cpu a b c previdle rest </proc/stat
	prevtotal=$((a + b + c + previdle))
	sleep 0.5
	read cpu a b c idle rest </proc/stat
	total=$((a + b + c + idle))
	cpu=$((100 * ((total - prevtotal) - (idle - previdle)) / (total - prevtotal)))
	echo -e " $cpu% cpu"
}

print_mem() {
	mem=$(free -m | sed -n '2p' | awk '{printf ("%.0f%\n", ""$3/$2*100"")}')

	printf " %s" "$mem"
}
# 

black="#1e222a"
white="#D8DEE9"
grey="#373d49"
blue="#81A1C1"
blue2="#5E81AC"
blue3="#88C0D0"
blue4="#8FBCBB"
red="#d47d85"
green="#A3BE8C"
pink="#B48EAD"
yellow="#EBCB8B"
orange="#D08770"
darkblue="#7292b2"

while true; do
	xsetroot -name "^c$black^^b$blue^  ^b$green^ $(print_mem) $(dwm_cpu) ^b$blue^^c$black^ $(dwm_network) ^c$black^^b$green^ $(dwm_battery) ^b$pink^ $(dwm_date) ^b#81A1C1^ $(dwm_alsa)"
	sleep 0.5
done
