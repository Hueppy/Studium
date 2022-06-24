using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class TransportRegulationRepository : Repository<TransportRegulation>
{    
    public TransportRegulationRepository(IConnector connector) : base(connector)
    {
    }

    protected override string Table => "TRANSPORTVORSCHRIFT";
    protected override string KeyField => "ID_TRANSPORTVORSCHRIFT";

    protected override string Insert => @"
INSERT INTO TRANSPORTVORSCHRIFT
  (NAME_TRANSPORTVORSCHRIFT, BESCHREIBUNG_T_VORSCHRIFT, ID_TRANSPORTVORSCHRIFT)
VALUES
  (:Name, :Description, :Id)";

    protected override string Update => @"
UPDATE TRANSPORTVORSCHRIFT
SET
  NAME_TRANSPORTVORSCHRIFT = :Name,
  BESCHREIBUNG_T_VORSCHRIFT = :Description
WHERE
  ID_TRANSPORTVORSCHRIFT = :Id";

    protected override async Task Read(TransportRegulation obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Name = await row.AsString("NAME_TRANSPORTVORSCHRIFT") ?? string.Empty;
        obj.Description = await row.AsString("BESCHREIBUNG_T_VORSCHRIFT") ?? string.Empty;
    }

    protected override long GetId(TransportRegulation obj)
    {
        return obj.Id;
    }


    protected override void SetId(TransportRegulation obj, long id)
    {
        obj.Id = id;
    }

    protected override void Write(TransportRegulation obj, IParameters parameters)
    {
        parameters.Add("Name", obj.Name);
        parameters.Add("Description", obj.Description);
        parameters.Add("Id", obj.Id);
    }
}
