# Virtual machine preparation

We used the following steps to prepare the virtual machine that you are currently using.

## Operating system installation

We used the official ISO of Ubuntu 20.04 and followed the installation process
of "Minimal installation".

We also changed the kernel parameter `systemd.unified_cgroup_hierarchy` to `0`,
which is required by the current version of BenchExec. I.e., we executed

```
echo 'GRUB_CMDLINE_LINUX_DEFAULT="${GRUB_CMDLINE_LINUX_DEFAULT} systemd.unified_cgroup_hierarchy=0"' | sudo tee /etc/default/grub.d/cgroupsv1-for-benchexec.cfg
sudo update-grub
```

Note that this needs a reboot to take effect.


## Dependencies

We installed the following packages, which are needed to prepare the artifact and for convenience:
```
sudo apt-get install -y python-is-python3
sudo apt-get install -y git
```

For Kratos2, we installed the following dependencies:
```
sudo apt-get install -y python3-pip
sudo pip install pycparser
```

For CPAchecker, we installed the following dependencies:
```
sudo apt-get install -y openjdk-11-jre
```

For VeriAbs, we installed the following dependencies:
```
sudo apt-get install -y gcc-multilib
```

For running the experiments, we installed and configured the following dependencies:
```
sudo add-apt-repository -y ppa:sosy-lab/benchmarking
sudo apt-get install -y benchexec
sudo usermod -a -G benchexec ae
```

For analysis of the experimental results, we installed the following dependencies:
```
sudo apt-get install -y r-base
sudo Rscript dependencies.R  # script from this directory
sudo apt-get install -y texlive
```


## Compared tools

Create the directory for the artifact:
```
mkdir artifact && cd artifact
```

Download the compared tools:
```
mkdir tools
pushd tools

wget https://kratos.fbk.eu/releases/kratos-2.0-linux64.tar.gz
tar -xzf kratos-2.0-linux64.tar.gz
mv kratos-2.0-linux64 kratos2
rm kratos-2.0-linux64.tar.gz

wget https://cpachecker.sosy-lab.org/CPAchecker-2.2-unix.zip
unzip CPAchecker-2.2-unix.zip
mv CPAchecker-2.2-unix CPAchecker
rm CPAchecker-2.2-unix.zip

popd
```

Add both tool executables to PATH permanently:

```
echo 'export PATH="/home/ae/artifact/tools/kratos2/bin/:$PATH"' >> /home/ae/.bashrc
echo 'export PYTHONPATH="/home/ae/artifact/tools/kratos2/tools:/home/ae/artifact/experiments/"' >> /home/ae/.bashrc
echo 'export PATH="/home/ae/artifact/tools/CPAchecker/scripts/:$PATH"' >> /home/ae/.bashrc
source /home/ae/.bashrc
```


## Benchmarks

Download the `svcomp22` version of the benchmarks from the official SV-COMP repository.

```
pushd benchmarks
git clone --depth 1 --branch svcomp22 https://gitlab.com/sosy-lab/benchmarking/sv-benchmarks.git
```

Generate the subset of benchmarks

```
pushd sv-benchmarks-subset
python generate_benchmarks.py 10 20
popd
popd
```

## Contents

Finally, we copied prepared files with the content of the artifact to directories
- `benchmarks`
- `docs`
- `examples`
- `experiments `
- `outputs`
- `results`
- `scripts`
- `vm-preparation`

and we made the scripts executable:

```
chmod a+x scripts/*.sh
chmod a+x scripts/*.py
```