using FHGuide.Shared.Models;

namespace FHGuide.Api.Services;

public interface IAuthenticator
{
	Task<Account> Authenticate(string email, string password);	
}
