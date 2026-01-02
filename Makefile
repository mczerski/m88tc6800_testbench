all: preset set_rf_front set_mixer set_lo set_pll set_bandwidth set_dac set_freq set_tune get_rf_strength

test: all
	./preset
	./set_rf_front
	./set_mixer
	./set_lo
	./set_pll
	./set_bandwidth
	./set_dac
	./set_tune
	./set_freq
	./get_rf_strength

common.o: common.c common.h
	gcc -c common.c -o common.o

original.o: original.c common.h gtm_hardware_fe.ko.h
	gcc -c original.c -o original.o

m88tc6800.o: m88tc6800.c common.h
	gcc -c m88tc6800.c -o m88tc6800.o

lib.a: common.o original.o m88tc6800.o
	ar -r lib.a common.o original.o m88tc6800.o

preset: preset.c common.h lib.a
	gcc preset.c -o preset -L. -l:lib.a

set_rf_front: set_rf_front.c common.h lib.a
	gcc set_rf_front.c -o set_rf_front -L. -l:lib.a

set_mixer: set_mixer.c common.h lib.a
	gcc set_mixer.c -o set_mixer -L. -l:lib.a

set_lo: set_lo.c common.h lib.a
	gcc set_lo.c -o set_lo -L. -l:lib.a

set_pll: set_pll.c common.h lib.a
	gcc set_pll.c -o set_pll -L. -l:lib.a

set_bandwidth: set_bandwidth.c common.h lib.a
	gcc set_bandwidth.c -o set_bandwidth -L. -l:lib.a

set_dac: set_dac.c common.h lib.a
	gcc set_dac.c -o set_dac -L. -l:lib.a

set_freq: set_freq.c common.h lib.a
	gcc set_freq.c -o set_freq -L. -l:lib.a

set_tune: set_tune.c common.h lib.a
	gcc set_tune.c -o set_tune -L. -l:lib.a

get_rf_strength: get_rf_strength.c common.h lib.a
	gcc get_rf_strength.c -o get_rf_strength -L. -l:lib.a
