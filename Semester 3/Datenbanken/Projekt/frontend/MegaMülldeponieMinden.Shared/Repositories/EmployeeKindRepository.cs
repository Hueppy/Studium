using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class EmployeeKindRepository : Repository<EmployeeKind>
{
    public EmployeeKindRepository(IConnector connector) : base(connector)
    {
    }

    protected override string Table => "PERSONALART";
    protected override string KeyField => "ID_PERSONALART";

    protected override string Insert => @"
INSERT INTO PERSONALART
(NAME_PERSONALART, BESCHREIBUNG_PERSONALART, ID_PERSONALART)
VALUES
(:Name, :Description, :Id)";

    protected override string Update => @"
UPDATE PERSONALART
SET
  NAME_PERSONALART = :Name, 
  BESCHREIBUNG_PERSONALART = :Description
WHERE
  ID_PERSONALART = :Id";

    protected override async Task Read(EmployeeKind obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Name = await row.AsString("NAME_PERSONALART") ?? string.Empty;
        obj.Description = await row.AsString("BESCHREIBUNG_PERSONALART") ?? string.Empty;
    }

    protected override long GetId(EmployeeKind obj)
    {
        return obj.Id;
    }


    protected override void SetId(EmployeeKind obj, long id)
    {
        obj.Id = id;
    }

    protected override void Write(EmployeeKind obj, IParameters parameters)
    {
        parameters.Add("Name", obj.Name);
        parameters.Add("Description", obj.Description);
        parameters.Add("Id", obj.Id);
    }
}
