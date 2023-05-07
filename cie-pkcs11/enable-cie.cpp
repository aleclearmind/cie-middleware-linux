#include "CSP/AbilitaCIE.h"
#include <cstdio>
#include <cassert>

extern "C" {
#include "unistd.h"

CK_RV AbilitaCIE(const char*  szPAN,
                          const char*  szPIN,
                          int* attempts,
                          PROGRESS_CALLBACK progressCallBack,
                          COMPLETED_CALLBACK completedCallBack);
}

static CK_RV progress_callback(const int progress,
                               const char* szMessage) {
  if (szMessage != NULL)
    fprintf(stderr, "Progress %d: %s\n", progress, szMessage);
  return CKR_OK;
}

static CK_RV completed_callback(const char* szPan,
                                const char* szName,
                                const char* ef_seriale) {
  fprintf(stderr, "Completed!\n");
  if (szPan != NULL)
    fprintf(stderr, "szPan: %s\n", szPan);
  if (szName != NULL)
    fprintf(stderr, "szName: %s\n", szName);
  if (ef_seriale != NULL)
    fprintf(stderr, "ef_seriale: %s\n", ef_seriale);
  return CKR_OK;
}


int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: ./enable-cie PAN PIN\n");
    return EXIT_FAILURE;
  }

  const char *szPAN = argv[1];
  const char *szPIN = argv[2];
  int attempts = 0;

  CK_FUNCTION_LIST_PTR proxy;
  CK_RV rv;

  rv = C_GetFunctionList (&proxy);
  assert (rv == CKR_OK);

  rv = proxy->C_Initialize (NULL);
  assert (rv == CKR_OK);

  CK_RV result = AbilitaCIE(szPAN, szPIN, &attempts, progress_callback, completed_callback);

  fprintf(stderr, "AbilitaCIE:\n  result = %ld\n  attempts = %d\n", result, attempts);

  rv = proxy->C_Finalize (NULL);
  assert (rv == CKR_OK);

  return EXIT_SUCCESS;
}
