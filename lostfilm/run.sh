rm -rf fbdir
rm -rf .local/share/luakit/
killall -9 Xvfb
killall -9 luakit

mkdir fbdir
Xvfb :99 -screen 0 1024x768x24 -fbdir fbdir &
XVBF_PID=$!

export DISPLAY=:99

luakit -u lostfilm.tv &
LUAKIT_PID=$!

sleep 20
WINDOW=`xdotool search LostFilm 2> /dev/null`
xdotool windowsize $WINDOW 1024 768
sleep 10

xdotool type --window $WINDOW "gi"
xdotool type --window $WINDOW "ld@hackerdom.ru"
xdotool key --window $WINDOW Tab
xdotool type --window $WINDOW "Qwer!234"
xdotool key --window $WINDOW Tab
xdotool key --window $WINDOW KP_Enter
sleep 10

xdotool mousemove --window $WINDOW 870 530
sleep 10

xdotool click --window $WINDOW 1
sleep 10

convert fbdir/Xvfb_screen0 screen.jpg
kill -9 $XVBF_PID
kill -9 $LUAKIT_PID
rm -rf fbdir
