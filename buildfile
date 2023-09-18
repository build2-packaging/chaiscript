import pkgs = {*/ -*-tests/ -*-samples/ -upstream/}
import tests = {*-tests/ *-samples/}
./: $pkgs
./: $tests: install = false
