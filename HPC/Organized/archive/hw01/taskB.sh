
CPU_DATA=$(lscpu | grep 'Model name' | cut -f 2 -d ":" | awk '{$1=$1}1')
echo "Hello World from $HOSTNAME CPU #$CPU_DATA"