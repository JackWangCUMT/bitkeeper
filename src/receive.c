#include "system.h"
#include "sccs.h" 

extern char *bin;

main(int ac,  char **av)
{
	int	c, new = 0;
	char	buf[MAXLINE], opts[MAXLINE] = "";
	char	*path;

	platformInit();  

	while ((c = getopt(ac, av, "acFiSv")) != -1) {
		switch (c) { 
		    case 'a': strcat(opts, " -a"); break;
		    case 'c': strcat(opts, " -c"); break;
		    case 'F': strcat(opts, " -F"); break;
		    case 'i': strcat(opts, " -i"); new =1; break;
		    case 'S': strcat(opts, " -S"); break;
		    case 'v': strcat(opts, " -v"); break;
		    default :
			fprintf(stderr, "unknow option <%c>\n", c);
			exit(1);
		}
	}
	unless (av[optind]) {
		if (sccs_cd2root(0, 0)) {
usage:			fprintf(stderr,
			"usage: bk receive [takepatch options] [pathname]\n");
			exit(1);
		}
	} else {
		path = av[optind++];
		if ((path == NULL) || (av[optind] != NULL)) goto usage;
		if (new && !isdir(path)) mkdirp(path);
		if (chdir(path) != 0) {
			perror(path);
			exit(1);
		}
	}
	sprintf(buf, "%sunwrap | %stakepatch %s", bin, bin, opts);
	return (system(buf));
}