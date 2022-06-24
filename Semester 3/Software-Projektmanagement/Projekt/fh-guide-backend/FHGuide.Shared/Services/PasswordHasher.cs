using System.Text;
using Microsoft.AspNetCore.Identity;
using FHGuide.Shared.Models;
using Sodium;

namespace FHGuide.Shared.Services;

public class PasswordHasher : IPasswordHasher<Account>
{
    public string HashPassword(Account account, string password)
    {
		var hash = PasswordHash.ArgonHashString(password);
		var bytes = Encoding.UTF8.GetBytes(hash);
		return Convert.ToBase64String(bytes);
    }

    public PasswordVerificationResult VerifyHashedPassword(Account account, string hashedPassword, string providedPassword)
    {
		var bytes = Convert.FromBase64String(hashedPassword);
		var hash = Encoding.UTF8.GetString(bytes);
		
		if (PasswordHash.ArgonHashStringVerify(hash, providedPassword))
		{
			return PasswordVerificationResult.Success;
		}

		return PasswordVerificationResult.Failed;
    }
}
