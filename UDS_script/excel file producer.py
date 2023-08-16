import datetime
import io
import re
import xlsxwriter

current_date = datetime.date.today()
TodayDate = current_date.strftime("%d/%m/%Y")
formatted_date = current_date.strftime("%d/%m/%Y")
header_filename = "uds_usr_datalink.h"
C_filename = "uds_usr_datalink.c"
output_filename = "UDS_datalink"
H = "static RET_T r"
K = "    }UDS_DID_"
B = "        UDS_SUB_"
L = "        UDS_DID_"
C = "            udsReadVar"
R = "r"

def create_worksheet(workbook, worksheet_name, data):
    # Truncate worksheet name to fit within 31 characters
    truncated_worksheet_name = worksheet_name[:31]
    worksheet = workbook.add_worksheet(truncated_worksheet_name)

    # Write the headers to the worksheet
    worksheet.write('A1', 'Name')
    worksheet.write('B1', 'Code')
    worksheet.write('C1', 'Data Type')
    worksheet.write('D1', 'Access')

    # Write the data to the worksheet
    row = 1
    for sub_name, code_name2, type4, R in data:
        worksheet.write(row, 0, sub_name)
        worksheet.write(row, 1, code_name2)
        worksheet.write(row, 2, type4)
        worksheet.write(row, 3, R)
        row += 1
        worksheet.set_column('A:A', 50)  # Set column A width to 20
        worksheet.set_column('B:B', 15)  # Set column B width to 15
        worksheet.set_column('C:C', 15)  # Set column C width to 15
        worksheet.set_column('D:D', 10)  # Set column D width to 10

with io.open(header_filename, mode="r") as header_file:
    file_content = header_file.read()

    for line in header_file:
        if line.startswith(L):
            words2 = line.split("=")
            b = words2[0].strip()
            a = words2[1].split(",")
            a1 = a[0].strip()
typedef_enum_pattern = r'typedef\s+enum\s+{([^}]*)}(\s*UDS_DID_\w+.*?);'
matches = re.findall(typedef_enum_pattern, file_content, re.DOTALL)

if matches:
    workbook = xlsxwriter.Workbook("UDS_datalink.xlsx")  # Create the Excel workbook
    worksheet_names = set()  # Store unique worksheet names
    for enum_content, enum_name in matches:
        enum_name = enum_name.strip()
        DID1 = enum_name.split(";")
        DID2 = DID1[0].strip().split("_0x")
        DID_name = DID2[0].strip()
        DID3 = DID2[1].strip().split("_t")
        DID_code = "0x" + DID3[0].strip()
        worksheet_name = f"{DID_name}_{DID_code}"
        if worksheet_name in worksheet_names:
            # Append an incremental number to the worksheet name to make it unique
            i = 1
            while f"{worksheet_name}_{i}" in worksheet_names:
                i += 1
            worksheet_name = f"{worksheet_name}_{i}"
        worksheet_names.add(worksheet_name)

        R = "r"
        data_pattern = r'UDS_SUB\w+.*?,'
        data_matches = re.findall(data_pattern, enum_content, re.DOTALL)
        if data_matches:
            data = []
            for lin in data_matches:
                words3 = lin.split("=")
                sub_name = words3[0].strip()
                code_name = words3[1].strip()
                code_name1 = code_name.split(",")
                code_name2 = code_name1[0].strip()
                with open(C_filename, 'r') as C_file:
                    contents = C_file.readlines()
                    for i, line1 in enumerate(contents):
                        if sub_name in line1:
                            if i + 2 < len(contents):
                                next_line = contents[i + 1].strip()
                                next2_line = contents[i + 2].strip()
                                next3_line = contents[i + 3].strip()
                                if "udsReadVar." in next_line:
                                    type1 = next_line.split("udsReadVar.")
                                    type2 = type1[1].strip()
                                    type3 = type2.split("[")
                                    type4 = type3[0].strip()
                                    break  # break must exist to access just the first sub_name in line,not the others
                                elif "udsReadVar." in next2_line and not next2_line.startswith(
                                        C) and not next_line.startswith("        case"):
                                    type1 = next2_line.split("udsReadVar.")
                                    type2 = type1[1].strip()
                                    type3 = type2.split("[")
                                    type4 = type3[0].strip()
                                elif "udsReadVar." in next3_line and not next_line.startswith("        case"):
                                    type1 = next3_line.split("udsReadVar.")
                                    type2 = type1[1].strip()
                                    type3 = type2.split("[")
                                    type4 = type3[0].strip()
                                else:
                                    type4 = "Null"
                data.append((sub_name, code_name2, type4, R))

            # Call the create_worksheet function to write data to the worksheet
            create_worksheet(workbook, worksheet_name, data)

    # Close the workbook after writing data
    workbook.close()

