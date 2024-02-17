{
  inputs = {
    nixpkgs.url = "github:NixOS/nixpkgs/nixos-unstable";

    epiflake = {
      url = "github:Sigmapitech/EpiFlake";
      inputs.nixpkgs.follows = "nixpkgs";
    };

    flake-utils.url = "github:numtide/flake-utils";
  };

  outputs = { self, epiflake, nixpkgs, flake-utils }:
    flake-utils.lib.eachSystem [ "x86_64-linux" ] (system:
      let
        pkgs = nixpkgs.legacyPackages.${system};
      in
      rec {
        formatter = pkgs.nixpkgs-fmt;

        devShells.default = pkgs.mkShell {
          hardeningDisable = [ "all" ];

          inputsFrom = pkgs.lib.attrsets.attrValues packages;
          packages = (epiflake.lib.ShellPkgs pkgs).base;
        };

        packages =
          let
            buildSharedLib = name: epiflake.lib.BuildEpitechCBinary
              pkgs
              {
                inherit name;
                src = ./.;

                enableParallelBuilding = true;
                installPhase = ''
                  runHook preInstall

                  mkdir -p $out/bin
                  cp ${name} $out/lib/${name}

                  runHook postInstall
                '';
              };
          in
          rec {
            default = alloc_stats;
            alloc_stats = buildSharedLib "liballoc_stats.so";
          };
      });
}
