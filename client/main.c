#include <stdio.h>
#include <inttypes.h>
#include <syslog.h>

#include "client.h"

#include <common/util.h>
#include <common/file.h>
#include <common/message.h>

static const char * LOG_PREFIX = "ftp_client";

/*  syslog(LOG_ERR, "Failed to open queue");
 *  LOG_INFO
 */

bool run_tests(void)
{
    const char * file_path = "/home/keith/Qt5.12.0/projects/ssca2_client/test.html";

    printf("Hello World!\n");

    File file = NULL;
    FILE * fp = fopen(file_path, "r+");

    if(! fp)
    {
        printf("Failed to open %s\n", file_path);
        return 1;
    }

    if(! load_file(&file, "test.html", fp))
    {
        printf("Failed to load file\n");
        return 1;
    }

    fclose(fp);

    const char * name = get_file_name(file);
    printf("Name: %s\n", name);

    DataBlock file_data = get_file_contents(file);
    printf("Returned file contents size : %lu\n", file_data.size);
    printf("Contents: '%.*s'\n", (int) file_data.size, file_data.data);

    Message message = make_upload_file_message(file, "/", "keith");
    assert(message != NULL && "Failed to make upload file message");

    destroy_file(&file);
    assert(file == NULL && "File not assigned to NULL after destroy operation");

    return true;
}


int main()
{
    // Open log connection with syslog
    openlog(LOG_PREFIX, LOG_CONS, LOG_DAEMON);

    klog(LOG_INFO, "FTP client started");

    run_tests();

    return 0;
}
