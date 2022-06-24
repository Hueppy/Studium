using MegaMülldeponieMinden.Shared.Database;
using MegaMülldeponieMinden.Shared.Models;

namespace MegaMülldeponieMinden.Shared.Repositories;

public class VehicleRepository : Repository<Vehicle>
{
    private Repository<Fleet> fleetRepository;
    
    public VehicleRepository(
        IConnector connector,
        Repository<Fleet> fleetRepository) : base(connector)
    {
        this.fleetRepository = fleetRepository;
    }

    protected override string Table => "FAHRZEUG";
    protected override string KeyField => "ID_FAHRZEUG";

    protected override string Insert => @"
INSERT INTO FAHRZEUG
  (NAME_FAHRZEUG, MODEL_FAHRZEUG, TANKGROESSE_FAHRZEUG, KAUFPREIS_FAHRZEUG, FUEHRERSCHEIN_FAHRZEUG, ID_FUHRPARK, ID_FAHRZEUG)
VALUES
  (:Name, :Model, :TankSize, :Price, :License, :Fleet, :Id)";

    protected override string Update => @"
UPDATE FAHRZEUG
SET
  NAME_FAHRZEUG = :Name,
  MODEL_FAHRZEUG = :Model,
  TANKGROESSE_FAHRZEUG = :TankSize,
  KAUFPREIS_FAHRZEUG = :Price,
  FUEHRERSCHEIN_FAHRZEUG = :License,
  ID_FUHRPARK = :Fleet
WHERE
  ID_FAHRZEUG = :Id";

    protected override async Task Read(Vehicle obj, IResultRow row)
    {
        obj.Id = await row.AsInt(this.KeyField) ?? -1;
        obj.Name = await row.AsString("NAME_FAHRZEUG") ?? string.Empty;
        obj.Model = await row.AsString("MODEL_FAHRZEUG") ?? string.Empty;
        obj.TankSize = await row.AsInt("TANKGROESSE_FAHRZEUG") ?? 0; 
        obj.Price = await row.AsInt("KAUFPREIS_FAHRZEUG") ?? 0;
        obj.License = await row.AsString("FUEHRERSCHEIN_FAHRZEUG") ?? string.Empty;
        
        obj.Fleet = await this.fleetRepository.Load(await row.AsInt("ID_FUHRPARK") ?? -1);
    }

    protected override long GetId(Vehicle obj)
    {
        return obj.Id;
    }


    protected override void SetId(Vehicle obj, long id)
    {
        obj.Id = id;
    }

    protected override void Write(Vehicle obj, IParameters parameters)
    {
        parameters.Add("Name", obj.Name);
        parameters.Add("Model", obj.Model);
        parameters.Add("TankSize", obj.TankSize);
        parameters.Add("Price", obj.Price);
        parameters.Add("License", obj.License);
        parameters.Add("Fleet", obj.Fleet.Id);
        parameters.Add("Id", obj.Id);
    }
}
