namespace MegaMülldeponieMinden.Shared.Models;

public class Material
{
    public long Id { get; set; }
    public string Name { get; set; }
    public string Description { get; set; }
    public double Amount { get; set; }
    public double Price { get; set; }
    public bool IsRecyclable { get; set; }
    
    public DisposalRegulation DisposalRegulation { get; set; }
    
    public MaterialKind MaterialKind { get; set; }
    
    public MaterialHazard MaterialHazard { get; set; }
    
    public Material Parent { get; set; }
    
    public TransportRegulation TransportRegulation { get; set; }
}
