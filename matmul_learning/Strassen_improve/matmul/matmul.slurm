#!/bin/bash

#SBATCH -p gpu
#SBATCH -J matmul
#SBATCH --nodes=2
#SBATCH --gres=gpu:2
#SBATCH --ntasks-per-node=1
#SBATCH -o logs/slurm_%j.out
#SBATCH -e logs/slurm_%j.err

hostname

./matmul_main
