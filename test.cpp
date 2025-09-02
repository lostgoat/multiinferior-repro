#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

static constexpr int k_nSecToMicros = 1000 * 1000;
static constexpr int k_nMilliToMiscros = 1000;

int DoParentLoop( int nChildPid )
{
	printf( "parent running \n" );

	printf( "waiting for child: %d\n", nChildPid );
	while( true )
	{
		int nStatus = 0;
		int nRet = waitpid( nChildPid, &nStatus, WNOHANG );
		printf( "parent waitpid returned: %d - %d\n", nRet, nStatus );
		usleep( 2 * k_nSecToMicros );

		if ( nRet == -1 )
			break;
	}

	printf( "parent exiting\n" );
	return 0;
}

int DoChildLoop()
{
	printf( "child started\n" );

	for ( int i = 0; i < 10; ++i )
	{
		printf( "child looping: %d\n", i );
		usleep( 500 * k_nMilliToMiscros );
	}

	printf( "child exiting\n" );
	return 0;
}

int main( int argc, char *argv[] )
{
	if ( argc > 1 && std::string( argv[ 1 ] ) == "child" )
	{
		return DoChildLoop();
	}

	printf( "Starting test\n" );

	pid_t pid = fork();
	if ( pid < 0 )
	{
		printf( "Error: fork failed" );
		return 1;
	}

	if ( pid == 0 )
	{
		char *args[] = { argv[ 0 ], ( char * )"child", nullptr };
		if ( execvp( argv[ 0 ], args ) == -1 )
		{
			printf( "Error: exec failed" );
			return 1;
		}
	}

	return DoParentLoop( pid );
}


