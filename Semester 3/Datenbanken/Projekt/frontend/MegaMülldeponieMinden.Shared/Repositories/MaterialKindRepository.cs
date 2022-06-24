using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class MaterialKindRepository : Repository<MaterialKind>
{    
    public MaterialKindRepository(IConnector connector) : base(connector)
    {
    }

    protected override string Table => "WERTSTOFFTYP";
    protected override string KeyField => "ID_WERTSTOFFTYP";

    protected override string Insert => @"
INSERT INTO WERTSTOFFTYP
  (NAME_WERTSTOFFTYP, BESCHREIBUNG_WERTSTOFFTYP, ID_WERTSTOFFTYP)
VALUES
  (:Name, :Description, :Id)";

    protected override string Update => @"
UPDATE WERTSTOFFTYP
SET
  NAME_WERTSTOFFTYP = :Name,
  BESCHREIBUNG_WERTSTOFFTYP = :Description
WHERE
  ID_WERTSTOFFTYP = :Id";

    protected override async Task Read(MaterialKind obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Name = await row.AsString("NAME_WERTSTOFFTYP") ?? string.Empty;
        obj.Description = await row.AsString("BESCHREIBUNG_WERTSTOFFTYP") ?? string.Empty;
    }

    protected override long GetId(MaterialKind obj)
    {
        return obj.Id;
    }


    protected override void SetId(MaterialKind obj, long id)
    {
        obj.Id = id;
    }

    protected override void Write(MaterialKind obj, IParameters parameters)
    {
        parameters.Add("Name", obj.Name);
        parameters.Add("Description", obj.Description);
        parameters.Add("Id", obj.Id);
    }
}
