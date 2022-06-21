obj_dir = .
#OPT = -Ofast=ip27 -mp  -p
#OPT = -O3 -apo -apokeep
NAME = 2dc_ac
OPT = -O3 -unroll_loops -pg
#OPT =  -pg

e2dc :   ${obj_dir}/pp_main.o ${obj_dir}/pf_data.o  \
          ${obj_dir}/ps_bljac.o  ${obj_dir}/ps_bjuti.o \
          ${obj_dir}/pf_cons.o ${obj_dir}/po_syst.o \
          ${obj_dir}/pf_util.o ${obj_dir}/po_util.o ;
	cc $(OPT) ${obj_dir}/pp_main.o ${obj_dir}/pf_data.o  \
          ${obj_dir}/ps_bljac.o  ${obj_dir}/ps_bjuti.o \
          ${obj_dir}/pf_cons.o ${obj_dir}/po_syst.o \
          ${obj_dir}/pf_util.o ${obj_dir}/po_util.o \
          -o ${NAME} -lm


${obj_dir}/pp_main.o : pp_main.c typedef.d ;
	cc $(OPT) -c pp_main.c
#	mv pp_main.o ${obj_dir}
${obj_dir}/pf_data.o : pf_data.c typedef.d declar.d ;
	cc $(OPT) -c pf_data.c
#	mv pf_data.o ${obj_dir}
${obj_dir}/ps_bljac.o : ps_bljac.c typedef.d declar.d patches.d ;
	cc $(OPT) -c ps_bljac.c
#	mv ps_bljac.o ${obj_dir}
${obj_dir}/ps_bjuti.o : ps_bjuti.c typedef.d declar.d patches.d ;
	cc $(OPT) -c ps_bjuti.c
#	mv ps_bjuti.o ${obj_dir}
${obj_dir}/pf_cons.o : pf_cons.c typedef.d declar.d ;
	cc $(OPT) -c pf_cons.c
#	mv pf_cons.o ${obj_dir}
${obj_dir}/pf_util.o : pf_util.c typedef.d declar.d ;
	cc $(OPT) -c pf_util.c
#	mv pf_util.o ${obj_dir}
${obj_dir}/po_util.o : po_util.c ;
	cc $(OPT) -c po_util.c
#	mv po_util.o ${obj_dir}
${obj_dir}/po_syst.o : po_syst.c ;
	cc $(OPT) -c po_syst.c
#	mv po_syst.o ${obj_dir}


clean:
	rm *.o 2dc_ac
#	rm obj/*.o 2dc_ac
