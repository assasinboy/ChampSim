#!/bin/bash
root_dir="`pwd`"
#spec_dir="/home/usk6037/nikos_paper/Champ_sim/"
#run_command = " ./run_champsim.sh bimodal-no-no-no-no-lru-1core 5 50 "
benchmark_dir="${root_dir}/runTraces"

#if [ ! "${1}" == "test" ] && [ ! "${1}" == "train" ] && [ ! "${1}" == "ref" ]; then
#  echo "Please provide workload size [test,train,ref] "
#  exit
#fi


workload=$1
run_command="./run_champsim.sh bimodal-no-no-no-no-perfect_cache-1core 5 50"
run_dir="/nfs-scratch/usk6037/ChampSim"
rm -rf ${benchmark_dir}
mkdir ${benchmark_dir}

for benchmark in lbm_94B sphinx3_883B tonto_422B calculix_2655B
do
	echo ${benchmark}
	mkdir ${benchmark_dir}/${benchmark}
	cd ${benchmark_dir}/${benchmark}
	cp ${root_dir}/script.condor .
	echo "#!/bin/bash">> ${benchmark}.sh
	echo "cd ${run_dir}" >> ${benchmark}.sh
	echo "${run_command}${benchmark}.trace.xz" >> ${benchmark}.sh
#	echo "make optimization BENCHMARK=${benchmark} WORKLOAD=${workload}" >> ${benchmark}.sh
	chmod +x ${benchmark}.sh
    mv script.condor ${benchmark}.condor
    echo "InitialDir = ${benchmark_dir}/${benchmark}" >> ${benchmark}.condor
    echo "Executable = ${benchmark_dir}/${benchmark}/${benchmark}.sh" >> ${benchmark}.condor
    echo "Queue" >> ${benchmark}.condor
done
