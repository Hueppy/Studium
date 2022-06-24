using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class MaterialRepository : Repository<Material>
{
    private readonly Repository<DisposalRegulation> disposalRegulationRepository;
    private readonly Repository<MaterialKind> materialKindRepository;
    private readonly Repository<MaterialHazard> materialHazardRepository;
    private readonly Repository<TransportRegulation> transportRegulationRepository;

    public MaterialRepository(
        IConnector connector,
        Repository<DisposalRegulation> disposalRegulationRepository,
        Repository<MaterialKind> materialKindRepository,
        Repository<MaterialHazard> materialHazardRepository,
        Repository<TransportRegulation> transportRegulationRepository) : base(connector)
    {
        this.disposalRegulationRepository = disposalRegulationRepository;
        this.materialKindRepository = materialKindRepository;
        this.materialHazardRepository = materialHazardRepository;
        this.transportRegulationRepository = transportRegulationRepository;
    }

    protected override string Table => "WERTSTOFF";
    protected override string KeyField => "ID_WERTSTOFF";

    protected override string Insert => @"
INSERT INTO WERTSTOFF (
    ID_ENTSORGUNGSBESTIMMUNG,
    ID_WERTSTOFFTYP,
    ID_WERTSTOFFGEFAHRENSTUFE,
    WER_ID_WERTSTOFF,
    ID_TRANSPORTVORSCHRIFT,
    NAME_WERTSTOFF,
    BESCHREIBUNG_WERTSTOFF,
    MENGE_WERTSTOFF,
    PREIS_WERTSTOFF,
    RECYCLEBAR_WERTSTOFF,
    ID_WERTSTOFF
) VALUES (
    :DisposalRegulation, 
    :MaterialKind, 
    :MaterialHazard,
    :Parent,
    :TransportRegulation,
    :Name,
    :Description,
    :Amount,
    :Price,
    :Recyclable,
    :Id
)";

    protected override string Update => @"
UPDATE WERTSTOFF
SET
    ID_ENTSORGUNGSBESTIMMUNG = :DisposalRegulation,
    ID_WERTSTOFFTYP = :MaterialKind,
    ID_WERTSTOFFGEFAHRENSTUFE = :MaterialHazard,
    WER_ID_WERTSTOFF = :Parent,
    ID_TRANSPORTVORSCHRIFT = :TransportRegulation,
    NAME_WERTSTOFF = :Name,
    BESCHREIBUNG_WERTSTOFF = :Description,
    MENGE_WERTSTOFF = :Amount,
    PREIS_WERTSTOFF = :Price,
    RECYCLEBAR_WERTSTOFF = :Recyclable
WHERE
  ID_WERTSTOFF = :Id";

    protected override async Task Read(Material obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Name = await row.AsString("NAME_WERTSTOFF") ?? string.Empty;
        obj.Description = await row.AsString("BESCHREIBUNG_WERTSTOFF") ?? string.Empty;
        obj.Amount = await row.AsDouble("MENGE_WERTSTOFF") ?? 0;
        obj.Price = await row.AsDouble("PREIS_WERTSTOFF") ?? 0;
        obj.IsRecyclable = await row.AsBoolean("RECYCLEBAR_WERTSTOFF") ?? false;

        obj.DisposalRegulation = await disposalRegulationRepository.Load(await row.AsInt("ID_ENTSORGUNGSBESTIMMUNG") ?? -1);
        obj.MaterialKind = await materialKindRepository.Load(await row.AsInt("ID_WERTSTOFFTYP") ?? -1);
        obj.MaterialHazard = await materialHazardRepository.Load(await row.AsInt("ID_WERTSTOFFGEFAHRENSTUFE") ?? -1);
        obj.Parent = await Load(await row.AsInt("WER_ID_WERTSTOFF") ?? -1);
        obj.TransportRegulation = await transportRegulationRepository.Load(await row.AsInt("ID_TRANSPORTVORSCHRIFT") ?? -1);
    }

    protected override long GetId(Material obj)
    {
        return obj.Id;
    }


    protected override void SetId(Material obj, long id)
    {
        obj.Id = id;
    }

    protected override void Write(Material obj, IParameters parameters)
    {
        parameters.Add("DisposalRegulation", obj.DisposalRegulation?.Id);
        parameters.Add("MaterialKind", obj.MaterialKind?.Id);
        parameters.Add("MaterialHazard", obj.MaterialHazard?.Id);
        parameters.Add("Parent", obj.Parent?.Id);
        parameters.Add("TransportRegulation", obj.TransportRegulation?.Id);
        parameters.Add("Name", obj.Name);
        parameters.Add("Description", obj.Description);
        parameters.Add("Amount", obj.Amount);
        parameters.Add("Price", obj.Price);
        parameters.Add("Recyclable", obj.IsRecyclable ? 1 : 0);
        parameters.Add("Id", obj.Id);
    }
}
