FOR %%T IN (5) DO (
	.\makedata.exe -C 4 -T %%T -v 4.25 -v 4.625 -v 5.00 -v 5.375 -v 5.75 > stdout_C2_T%%T.txt
	FOR %%M IN (0.05, 0.10, 0.15, 0.20, 0.25, 0.30) DO (
		FOR %%R IN (0.30, 0.40, 0.50, 0.60, 0.70, 0.80, 0.90, 1.00) DO (
			.\makeConst.exe -M %%M -R %%R >> stdout_C4_T%%T.txt
			glpsol.exe -m WFmodel_120205.mod -d Margin_%%M_Ratio_%%R.dat -d WFmodel_Term_%%T.dat -d Class_2_Term_%%T_data.dat --check --wlp WFModel_C4_T%%T_M%%M_R%%R.lp >> stdout_C4_T%%T.txt
			scip-2.1.1.mingw.x86_64.intel.opt.spx.exe -c "read WFModel_C4_T%%T_M%%M_R%%R.lp" -c "optimize" -c "write" -c "solution" -c "WFModel_C4_T%%T_M%%M_R%%R.sol" -c "quit" >> stdout_C4_T%%T.txt
		)
	)
	python.exe parse_stdout.py stdout_C4_T%%T.txt stdout_C4_T%%T_data.txt
)
