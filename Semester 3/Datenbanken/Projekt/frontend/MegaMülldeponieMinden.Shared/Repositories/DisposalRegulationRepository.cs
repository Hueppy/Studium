using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class DisposalRegulationRepository : Repository<DisposalRegulation>
{    
    public DisposalRegulationRepository(IConnector connector) : base(connector)
    {
    }

    protected override string Table => "ENTSORGUNGSBESTIMMUNG";
    protected override string KeyField => "ID_ENTSORGUNGSBESTIMMUNG";

    protected override string Insert => @"
INSERT INTO ENTSORGUNGSBESTIMMUNG
  (NAME_ENTSORGUNGSBESTIMMUNG, BESCHREIBUNG_E_BESTIMMUNG, ID_ENTSORGUNGSBESTIMMUNG)
VALUES
  (:Name, :Description, :Id)";

    protected override string Update => @"
UPDATE ENTSORGUNGSBESTIMMUNG
SET
  NAME_ENTSORGUNGSBESTIMMUNG = :Name,
  BESCHREIBUNG_E_BESTIMMUNG = :Description
WHERE
  ID_ENTSORGUNGSBESTIMMUNG = :Id";

    protected override async Task Read(DisposalRegulation obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Name = await row.AsString("NAME_ENTSORGUNGSBESTIMMUNG") ?? string.Empty;
        obj.Description = await row.AsString("BESCHREIBUNG_E_BESTIMMUNG") ?? string.Empty;
    }

    protected override long GetId(DisposalRegulation obj)
    {
        return obj.Id;
    }


    protected override void SetId(DisposalRegulation obj, long id)
    {
        obj.Id = id;
    }

    protected override void Write(DisposalRegulation obj, IParameters parameters)
    {
        parameters.Add("Name", obj.Name);
        parameters.Add("Description", obj.Description);
        parameters.Add("Id", obj.Id);
    }
}
