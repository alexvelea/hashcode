if [ $1 ]; then
    python plot_start_end_coords.py < tests/test-$1.in
else
    echo "put a test number as first param"
fi
