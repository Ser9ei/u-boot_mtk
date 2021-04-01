/*
 * Copyright (C) 2016 Piotr Dymacz <piotr@dymacz.pl>
 *
 * SPDX-License-Identifier: GPL-2.0
 */

/*
 * Custom/miscellaneous commands
 */

#include <common.h>
#include <command.h>


#if defined(CONFIG_NETCONSOLE)
/*
 * Start NetConsole
 */
int do_start_nc(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	return(run_command("setenv stdin nc;setenv stdout nc;setenv stderr nc;version;", 0));
}

U_BOOT_CMD(startnc, 1, 0, do_start_nc, "start net console\n", NULL);

/*
 * Start Serial Console
 */
int do_start_sc(cmd_tbl_t * cmdtp, int flag, int argc, char *argv[]){
	return(run_command("setenv stdin serial;setenv stdout serial;setenv stderr serial;version;", 0));
}

U_BOOT_CMD(startsc, 1, 0, do_start_sc, "start serial console\n", NULL);

#endif /* if defined(CONFIG_NETCONSOLE) */
