set xlabel "binary heap"
set ylabel "hollow heap"
plot "heaps_insert_comparison_swaps.dat" w linesp
set terminal png size 400,300 enhanced font "Arial,10"
set output "heaps_insert_comparison_swaps.png"
replot

set xlabel "binary heap"
set ylabel "hollow heap"
plot "heaps_insert_comparison_times.dat" w linesp
set terminal png size 400,300 enhanced font "Arial,10"
set output "heaps_insert_comparison_times.png"
replot

set xlabel "binary heap"
set ylabel "hollow heap"
plot "heaps_update_comparison_swaps.dat" w linesp
set terminal png size 400,300 enhanced font "Arial,10"
set output "heaps_update_comparison_swaps.png"
replot

set xlabel "binary heap"
set ylabel "hollow heap"
plot "heaps_update_comparison_times.dat" w linesp
set terminal png size 400,300 enhanced font "Arial,10"
set output "heaps_update_comparison_times.png"
replot

set xlabel "binary heap"
set ylabel "hollow heap"
plot "heaps_deletemin_comparison_swaps.dat" w linesp
set terminal png size 400,300 enhanced font "Arial,10"
set output "heaps_deletemin_comparison_swaps.png"
replot

set xlabel "binary heap"
set ylabel "hollow heap"
plot "heaps_deletemin_comparison_times.dat" w linesp
set terminal png size 400,300 enhanced font "Arial,10"
set output "heaps_deletemin_comparison_times.png"
replot






set format x "%.0s*10^%T"
set format y "%.0s*10^%T"
set xlabel "m"
set ylabel "dijkstra hollow heap"
plot "dijkstra_timeshh_m.dat" w linesp
set terminal png size 640,480 enhanced font "Arial,8"
set output "dijkstra_timeshh_m.png"
replot

set format x "%.0s*10^%T"
set format y "%.0s*10^%T"
set xlabel "m"
set ylabel "dijkstra binary heap"
plot "dijkstra_timesbh_m.dat" w linesp
set terminal png size 640,480 enhanced font "Arial,8"
set output "dijkstra_timesbh_m.png"
replot

set format x "%.0s*10^%T"
set format y "%.0s*10^%T"
set xlabel "n"
set ylabel "dijkstra hollow heap"
plot "dijkstra_timeshh_n.dat" w linesp
set terminal png size 640,480 enhanced font "Arial,8"
set output "dijkstra_timeshh_n.png"
replot

set format x "%.0s*10^%T"
set format y "%.0s*10^%T"
set xlabel "n"
set ylabel "dijkstra binary heap"
plot "dijkstra_timesbh_n.dat" w linesp
set terminal png size 640,480 enhanced font "Arial,8"
set output "dijkstra_timesbh_n.png"
replot