/******************************************************************************
 *
 * Module Name: tbxface - Public interfaces to the ACPI subsystem
 *                         ACPI table oriented interfaces
 *              $Revision: 42 $
 *
 *****************************************************************************/

/******************************************************************************
 *
 * 1. Copyright Notice
 *
 * Some or all of this work - Copyright (c) 1999, 2000, 2001, Intel Corp.
 * All rights reserved.
 *
 * 2. License
 *
 * 2.1. This is your license from Intel Corp. under its intellectual property
 * rights.  You may have additional license terms from the party that provided
 * you this software, covering your right to use that party's intellectual
 * property rights.
 *
 * 2.2. Intel grants, free of charge, to any person ("Licensee") obtaining a
 * copy of the source code appearing in this file ("Covered Code") an
 * irrevocable, perpetual, worldwide license under Intel's copyrights in the
 * base code distributed originally by Intel ("Original Intel Code") to copy,
 * make derivatives, distribute, use and display any portion of the Covered
 * Code in any form, with the right to sublicense such rights; and
 *
 * 2.3. Intel grants Licensee a non-exclusive and non-transferable patent
 * license (with the right to sublicense), under only those claims of Intel
 * patents that are infringed by the Original Intel Code, to make, use, sell,
 * offer to sell, and import the Covered Code and derivative works thereof
 * solely to the minimum extent necessary to exercise the above copyright
 * license, and in no event shall the patent license extend to any additions
 * to or modifications of the Original Intel Code.  No other license or right
 * is granted directly or by implication, estoppel or otherwise;
 *
 * The above copyright and patent license is granted only if the following
 * conditions are met:
 *
 * 3. Conditions
 *
 * 3.1. Redistribution of Source with Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification with rights to further distribute source must include
 * the above Copyright Notice, the above License, this list of Conditions,
 * and the following Disclaimer and Export Compliance provision.  In addition,
 * Licensee must cause all Covered Code to which Licensee contributes to
 * contain a file documenting the changes Licensee made to create that Covered
 * Code and the date of any change.  Licensee must include in that file the
 * documentation of any changes made by any predecessor Licensee.  Licensee
 * must include a prominent statement that the modification is derived,
 * directly or indirectly, from Original Intel Code.
 *
 * 3.2. Redistribution of Source with no Rights to Further Distribute Source.
 * Redistribution of source code of any substantial portion of the Covered
 * Code or modification without rights to further distribute source must
 * include the following Disclaimer and Export Compliance provision in the
 * documentation and/or other materials provided with distribution.  In
 * addition, Licensee may not authorize further sublicense of source of any
 * portion of the Covered Code, and must include terms to the effect that the
 * license from Licensee to its licensee is limited to the intellectual
 * property embodied in the software Licensee provides to its licensee, and
 * not to intellectual property embodied in modifications its licensee may
 * make.
 *
 * 3.3. Redistribution of Executable. Redistribution in executable form of any
 * substantial portion of the Covered Code or modification must reproduce the
 * above Copyright Notice, and the following Disclaimer and Export Compliance
 * provision in the documentation and/or other materials provided with the
 * distribution.
 *
 * 3.4. Intel retains all right, title, and interest in and to the Original
 * Intel Code.
 *
 * 3.5. Neither the name Intel nor any other trademark owned or controlled by
 * Intel shall be used in advertising or otherwise to promote the sale, use or
 * other dealings in products derived from or relating to the Covered Code
 * without prior written authorization from Intel.
 *
 * 4. Disclaimer and Export Compliance
 *
 * 4.1. INTEL MAKES NO WARRANTY OF ANY KIND REGARDING ANY SOFTWARE PROVIDED
 * HERE.  ANY SOFTWARE ORIGINATING FROM INTEL OR DERIVED FROM INTEL SOFTWARE
 * IS PROVIDED "AS IS," AND INTEL WILL NOT PROVIDE ANY SUPPORT,  ASSISTANCE,
 * INSTALLATION, TRAINING OR OTHER SERVICES.  INTEL WILL NOT PROVIDE ANY
 * UPDATES, ENHANCEMENTS OR EXTENSIONS.  INTEL SPECIFICALLY DISCLAIMS ANY
 * IMPLIED WARRANTIES OF MERCHANTABILITY, NONINFRINGEMENT AND FITNESS FOR A
 * PARTICULAR PURPOSE.
 *
 * 4.2. IN NO EVENT SHALL INTEL HAVE ANY LIABILITY TO LICENSEE, ITS LICENSEES
 * OR ANY OTHER THIRD PARTY, FOR ANY LOST PROFITS, LOST DATA, LOSS OF USE OR
 * COSTS OF PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES, OR FOR ANY INDIRECT,
 * SPECIAL OR CONSEQUENTIAL DAMAGES ARISING OUT OF THIS AGREEMENT, UNDER ANY
 * CAUSE OF ACTION OR THEORY OF LIABILITY, AND IRRESPECTIVE OF WHETHER INTEL
 * HAS ADVANCE NOTICE OF THE POSSIBILITY OF SUCH DAMAGES.  THESE LIMITATIONS
 * SHALL APPLY NOTWITHSTANDING THE FAILURE OF THE ESSENTIAL PURPOSE OF ANY
 * LIMITED REMEDY.
 *
 * 4.3. Licensee shall not export, either directly or indirectly, any of this
 * software or system incorporating such software without first obtaining any
 * required license or other approval from the U. S. Department of Commerce or
 * any other agency or department of the United States Government.  In the
 * event Licensee exports any such software from the United States or
 * re-exports any such software from a foreign destination, Licensee shall
 * ensure that the distribution and export/re-export of the software is in
 * compliance with all laws, regulations, orders, or other restrictions of the
 * U.S. Export Administration Regulations. Licensee agrees that neither it nor
 * any of its subsidiaries will export/re-export any technical data, process,
 * software, or service, directly or indirectly, to any country for which the
 * United States government or any agency thereof requires an export license,
 * other governmental approval, or letter of assurance, without first obtaining
 * such license, approval or letter.
 *
 *****************************************************************************/

#define __TBXFACE_C__

#include "acpi.h"
#include "acnamesp.h"
#include "acinterp.h"
#include "actables.h"


#define _COMPONENT          ACPI_TABLES
        MODULE_NAME         ("tbxface")


/*******************************************************************************
 *
 * FUNCTION:    AcpiLoadTables
 *
 * PARAMETERS:  None
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to load the ACPI tables from the
 *              provided RSDT
 *
 ******************************************************************************/

ACPI_STATUS
AcpiLoadTables (void)
{
    ACPI_PHYSICAL_ADDRESS   RsdpPhysicalAddress;
    ACPI_STATUS             Status;
    UINT32                  NumberOfTables = 0;


    FUNCTION_TRACE ("AcpiLoadTables");


    /* Ensure that ACPI has been initialized */

    ACPI_IS_INITIALIZATION_COMPLETE (Status);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }


    /* Get the RSDP */

    Status = AcpiOsGetRootPointer (ACPI_LOGICAL_ADDRESSING, 
                    &RsdpPhysicalAddress);
    if (ACPI_FAILURE (Status))
    {
        REPORT_ERROR (("AcpiLoadTables: Could not get RSDP, %s\n",
                        AcpiFormatException (Status)));
        goto ErrorExit;
    }

    /* Map and validate the RSDP */

    Status = AcpiTbVerifyRsdp (RsdpPhysicalAddress);
    if (ACPI_FAILURE (Status))
    {
        REPORT_ERROR (("AcpiLoadTables: RSDP Failed validation: %s\n",
                        AcpiFormatException (Status)));
        goto ErrorExit;
    }

    /* Get the RSDT via the RSDP */

    Status = AcpiTbGetTableRsdt (&NumberOfTables);
    if (ACPI_FAILURE (Status))
    {
        REPORT_ERROR (("AcpiLoadTables: Could not load RSDT: %s\n",
                        AcpiFormatException (Status)));
        goto ErrorExit;
    }

    /* Now get the rest of the tables */

    Status = AcpiTbGetAllTables (NumberOfTables, NULL);
    if (ACPI_FAILURE (Status))
    {
        REPORT_ERROR (("AcpiLoadTables: Error getting required tables (DSDT/FADT/FACS): %s\n",
                        AcpiFormatException (Status)));
        goto ErrorExit;
    }

    ACPI_DEBUG_PRINT ((ACPI_DB_OK, "ACPI Tables successfully loaded\n"));


    /* Load the namespace from the tables */

    Status = AcpiNsLoadNamespace ();
    if (ACPI_FAILURE (Status))
    {
        REPORT_ERROR (("AcpiLoadTables: Could not load namespace: %s\n",
                        AcpiFormatException (Status)));
        goto ErrorExit;
    }

    return_ACPI_STATUS (AE_OK);


ErrorExit:
    REPORT_ERROR (("AcpiLoadTables: Could not load tables: %s\n",
                    AcpiFormatException (Status)));

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiLoadTable
 *
 * PARAMETERS:  TablePtr        - pointer to a buffer containing the entire
 *                                table to be loaded
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to load a table from the caller's
 *              buffer.  The buffer must contain an entire ACPI Table including
 *              a valid header.  The header fields will be verified, and if it
 *              is determined that the table is invalid, the call will fail.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiLoadTable (
    ACPI_TABLE_HEADER       *TablePtr)
{
    ACPI_STATUS             Status;
    ACPI_TABLE_DESC         TableInfo;


    FUNCTION_TRACE ("AcpiLoadTable");


    /* Ensure that ACPI has been initialized */

    ACPI_IS_INITIALIZATION_COMPLETE (Status);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    if (!TablePtr)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Copy the table to a local buffer */

    Status = AcpiTbGetTable (0, TablePtr, &TableInfo);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Install the new table into the local data structures */

    Status = AcpiTbInstallTable (NULL, &TableInfo);
    if (ACPI_FAILURE (Status))
    {
        /* Free table allocated by AcpiTbGetTable */

        AcpiTbDeleteSingleTable (&TableInfo);
        return_ACPI_STATUS (Status);
    }


    Status = AcpiNsLoadTable (TableInfo.InstalledDesc, AcpiGbl_RootNode);
    if (ACPI_FAILURE (Status))
    {
        /* Uninstall table and free the buffer */

        AcpiTbUninstallTable (TableInfo.InstalledDesc);
        return_ACPI_STATUS (Status);
    }


    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiUnloadTable
 *
 * PARAMETERS:  TableType     - Type of table to be unloaded
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This routine is used to force the unload of a table
 *
 ******************************************************************************/

ACPI_STATUS
AcpiUnloadTable (
    ACPI_TABLE_TYPE         TableType)
{
    ACPI_TABLE_DESC         *ListHead;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AcpiUnloadTable");


    /* Ensure that ACPI has been initialized */

    ACPI_IS_INITIALIZATION_COMPLETE (Status);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /* Parameter validation */

    if (TableType > ACPI_TABLE_MAX)
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /* Find all tables of the requested type */

    ListHead = &AcpiGbl_AcpiTables[TableType];
    do
    {
        /*
         * Delete all namespace entries owned by this table.  Note that these
         * entries can appear anywhere in the namespace by virtue of the AML
         * "Scope" operator.  Thus, we need to track ownership by an ID, not
         * simply a position within the hierarchy
         */
        AcpiNsDeleteNamespaceByOwner (ListHead->TableId);

        /* Delete (or unmap) the actual table */

        AcpiTbDeleteAcpiTable (TableType);

    } while (ListHead != &AcpiGbl_AcpiTables[TableType]);

    return_ACPI_STATUS (AE_OK);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiGetTableHeader
 *
 * PARAMETERS:  TableType       - one of the defined table types
 *              Instance        - the non zero instance of the table, allows
 *                                support for multiple tables of the same type
 *                                see AcpiGbl_AcpiTableFlag
 *              OutTableHeader  - pointer to the ACPI_TABLE_HEADER if successful
 *
 * DESCRIPTION: This function is called to get an ACPI table header.  The caller
 *              supplies an pointer to a data area sufficient to contain an ACPI
 *              ACPI_TABLE_HEADER structure.
 *
 *              The header contains a length field that can be used to determine
 *              the size of the buffer needed to contain the entire table.  This
 *              function is not valid for the RSD PTR table since it does not
 *              have a standard header and is fixed length.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiGetTableHeader (
    ACPI_TABLE_TYPE         TableType,
    UINT32                  Instance,
    ACPI_TABLE_HEADER       *OutTableHeader)
{
    ACPI_TABLE_HEADER       *TblPtr;
    ACPI_STATUS             Status;


    FUNCTION_TRACE ("AcpiGetTableHeader");


    /* Ensure that ACPI has been initialized */

    ACPI_IS_INITIALIZATION_COMPLETE (Status);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    if ((Instance == 0)                 ||
        (TableType == ACPI_TABLE_RSDP)  ||
        (!OutTableHeader))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Check the table type and instance */

    if ((TableType > ACPI_TABLE_MAX)    ||
        (IS_SINGLE_TABLE (AcpiGbl_AcpiTableData[TableType].Flags) &&
         Instance > 1))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /* Get a pointer to the entire table */

    Status = AcpiTbGetTablePtr (TableType, Instance, &TblPtr);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /*
     * The function will return a NULL pointer if the table is not loaded
     */
    if (TblPtr == NULL)
    {
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    /*
     * Copy the header to the caller's buffer
     */
    MEMCPY ((void *) OutTableHeader, (void *) TblPtr,
                sizeof (ACPI_TABLE_HEADER));

    return_ACPI_STATUS (Status);
}


/*******************************************************************************
 *
 * FUNCTION:    AcpiGetTable
 *
 * PARAMETERS:  TableType       - one of the defined table types
 *              Instance        - the non zero instance of the table, allows
 *                                support for multiple tables of the same type
 *                                see AcpiGbl_AcpiTableFlag
 *              RetBuffer       - pointer to a structure containing a buffer to
 *                                receive the table
 *
 * RETURN:      Status
 *
 * DESCRIPTION: This function is called to get an ACPI table.  The caller
 *              supplies an OutBuffer large enough to contain the entire ACPI
 *              table.  The caller should call the AcpiGetTableHeader function
 *              first to determine the buffer size needed.  Upon completion
 *              the OutBuffer->Length field will indicate the number of bytes
 *              copied into the OutBuffer->BufPtr buffer.  This table will be
 *              a complete table including the header.
 *
 ******************************************************************************/

ACPI_STATUS
AcpiGetTable (
    ACPI_TABLE_TYPE         TableType,
    UINT32                  Instance,
    ACPI_BUFFER             *RetBuffer)
{
    ACPI_TABLE_HEADER       *TblPtr;
    ACPI_STATUS             Status;
    UINT32                  RetBufLen;


    FUNCTION_TRACE ("AcpiGetTable");


    /* Ensure that ACPI has been initialized */

    ACPI_IS_INITIALIZATION_COMPLETE (Status);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /*
     *  If we have a buffer, we must have a length too
     */
    if ((Instance == 0)                 ||
        (!RetBuffer)                    ||
        ((!RetBuffer->Pointer) && (RetBuffer->Length)))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }

    /* Check the table type and instance */

    if ((TableType > ACPI_TABLE_MAX)    ||
        (IS_SINGLE_TABLE (AcpiGbl_AcpiTableData[TableType].Flags) &&
         Instance > 1))
    {
        return_ACPI_STATUS (AE_BAD_PARAMETER);
    }


    /* Get a pointer to the entire table */

    Status = AcpiTbGetTablePtr (TableType, Instance, &TblPtr);
    if (ACPI_FAILURE (Status))
    {
        return_ACPI_STATUS (Status);
    }

    /*
     * AcpiTbGetTablePtr will return a NULL pointer if the
     * table is not loaded.
     */
    if (TblPtr == NULL)
    {
        return_ACPI_STATUS (AE_NOT_EXIST);
    }

    /*
     * Got a table ptr, assume it's ok and copy it to the user's buffer
     */
    if (TableType == ACPI_TABLE_RSDP)
    {
        /*
         *  RSD PTR is the only "table" without a header
         */
        RetBufLen = sizeof (RSDP_DESCRIPTOR);
    }
    else
    {
        RetBufLen = TblPtr->Length;
    }

    /*
     * Verify we have space in the caller's buffer for the table
     */
    if (RetBuffer->Length < RetBufLen)
    {
        RetBuffer->Length = RetBufLen;
        return_ACPI_STATUS (AE_BUFFER_OVERFLOW);
    }

    RetBuffer->Length = RetBufLen;

    MEMCPY ((void *) RetBuffer->Pointer, (void *) TblPtr, RetBufLen);

    return_ACPI_STATUS (AE_OK);
}


