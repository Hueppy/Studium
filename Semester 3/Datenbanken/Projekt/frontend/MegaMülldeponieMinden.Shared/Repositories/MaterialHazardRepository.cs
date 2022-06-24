using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class MaterialHazardRepository : Repository<MaterialHazard>
{    
    public MaterialHazardRepository(IConnector connector) : base(connector)
    {
    }

    protected override string Table => "WERTSTOFFGEFAHRENSTUFE";
    protected override string KeyField => "ID_WERTSTOFFGEFAHRENSTUFE";

    protected override string Insert => @"
INSERT INTO WERTSTOFFGEFAHRENSTUFE
  (NAME_WERTSTOFFGEFAHRENSTUFE, BESCHREIBUNG_W_GEFAHRENSTUFE, ID_WERTSTOFFGEFAHRENSTUFE)
VALUES
  (:Name, :Description, :Id)";

    protected override string Update => @"
UPDATE WERTSTOFFGEFAHRENSTUFE
SET
  NAME_WERTSTOFFGEFAHRENSTUFE = :Name,
  BESCHREIBUNG_W_GEFAHRENSTUFE = :Description
WHERE
  ID_WERTSTOFFGEFAHRENSTUFE = :Id";

    protected override async Task Read(MaterialHazard obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Name = await row.AsString("NAME_WERTSTOFFGEFAHRENSTUFE") ?? string.Empty;
        obj.Description = await row.AsString("BESCHREIBUNG_W_GEFAHRENSTUFE") ?? string.Empty;
    }

    protected override long GetId(MaterialHazard obj)
    {
        return obj.Id;
    }


    protected override void SetId(MaterialHazard obj, long id)
    {
        obj.Id = id;
    }

    protected override void Write(MaterialHazard obj, IParameters parameters)
    {
        parameters.Add("Name", obj.Name);
        parameters.Add("Description", obj.Description);
        parameters.Add("Id", obj.Id);
    }
}
