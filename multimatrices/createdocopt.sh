url=https://github.com/docopt/docopt.c;
if [ ! -d /tmp/docopt.c ]; then
    git clone $url /tmp/docopt.c
fi
python3 /tmp/docopt.c/docopt_c.py -o docopt.c matrices.docopt