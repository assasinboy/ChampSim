#!/bin/bash
root_dir="`pwd`"
benchmark_dir="${root_dir}/runTraces"

for benchmark in `ls ${benchmark_dir}`
do
	cd ${benchmark_dir}/${benchmark}
	echo Submitting ${benchmark}
	condor_submit ${benchmark}.condor
done
