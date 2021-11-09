
#install.packages('pedgene')
#install.packages('CompQuadForm')
#install.packages('Matrix')
#install.packages('kinship2')
#install.packages('quadprog')
#install.packages('gee')


rm(list=ls())
library('pedgene')
library('CompQuadForm')
library('Matrix')
library('kinship2')
library('quadprog')
library('gee')


########################################################################################################
########################################################################################################
### DJ Schaid
########################################################################################################
########################################################################################################



pedgeneLF=
function (ped, geno, map = NULL, male.dose = 2, weights = NULL, 
    checkpeds = TRUE, acc.davies = 1e-05) 
{
    verbose = FALSE
    call <- match.call()
    saveOpt <- options()
    options(stringsAsFactors = FALSE)
    kin2v <- sessionInfo()$otherPkgs$kinship2$Version
    if (is.null(kin2v)) {
        kin2v <- sessionInfo()$loadedOnly$kinship2$Version
    }
    if (as.numeric(substring(kin2v, 1, nchar(kheein2v) - 2)) < 1.5) {
        stop("kinship2 needs to be version 1.5.3 or later\n")
    }
    if (is.null(map)) {
        map <- data.frame(chrom = rep("unknown", ncol(geno) - 
            2), gene = rep("unknown", ncol(geno) - 2))
    }
    names(map) <- casefold(names(map))
    names(ped) <- casefold(names(ped))
    if (any(!(c("chrom", "gene") %in% names(map)))) {
        stop("map requires columns for chrom and gene")
    }
    map$chrom[map$chrom == 23] <- "X"
    if (any(!(c("ped", "person") %in% names(geno)))) {
        stop("geno requires columns 'ped' and 'person' ids")
    }
    keepped <- match(paste(geno$ped, geno$person, sep = "-"), 
        paste(ped$ped, ped$person, sep = "-"))
    geno <- geno[, !(names(geno) %in% c("ped", "person"))]
    if (nrow(map) != (ncol(geno))) {
        stop(paste("map rows (", nrow(map), ") and geno columns (", 
            ncol(geno), ") do not match \n", sep = ""))
    }
    xidx <- which(map$chrom == "X" | map$chrom == "x")
    if (length(xidx)) {
        xdosemale <- geno[ped$sex[keepped] == 1, xidx, drop = TRUE]
        if (sum(xdosemale > 1, na.rm = TRUE)) {
            stop("All male dose on X chromosome should be <= 1")
        }
    }
    if (any(!(c("ped", "person", "father", "mother", "sex", "trait") %in% 
        names(ped)))) {
        stop("Error: ped requires columns: ped, person, father, mother, sex, trait")
    }
    if (!("trait.adjusted" %in% names(ped))) {
        ped$trait.adjusted <- mean(ped$trait, na.rm = TRUE)
    }
    if (!is.null(weights)) {
        if (length(weights) != ncol(geno)) {
            stop(paste("Error: should have weights(", length(weights), 
                ") for every variant position(", ncol(geno), 
                ")", sep = ""))
        }
    }
    if (checkpeds) {
        uped <- unique(ped$ped)
        nped <- length(uped)
        for (i in 1:nped) {
            iped <- uped[i]
            temp.ped <- ped[ped$ped == iped, , drop = FALSE]
            if (nrow(temp.ped) > 1) {
                pedigreeChecks(temp.ped, male.code = 1, female.code = 2)
            }
        }
    }
    kinmat <- Matrix(with(ped, kinship(ped, id = paste(ped, person, 
        sep = "-"), dadid = ifelse(father > 0, paste(ped, father, 
        sep = "-"), as.character(father)), momid = ifelse(mother > 
        0, paste(ped, mother, sep = "-"), as.character(mother)), 
        sex = sex, chrtype = "autosome")))
    kinmat <- kinmat[keepped, keepped]
    if (any(map$chrom == "X")) {
        kinmatX <- Matrix(with(ped, kinship(ped, id = paste(ped, 
            person, sep = "-"), dadid = ifelse(father > 0, paste(ped, 
            father, sep = "-"), as.character(father)), momid = ifelse(mother > 
            0, paste(ped, mother, sep = "-"), as.character(mother)), 
            sex = sex, chrtype = "X")))
        kinmatX <- kinmatX[keepped, keepped]
    }
    else {
        kinmatX <- NULL
    }
    ped <- ped[keepped, ]
    missidx <- is.na(ped$trait) | apply(is.na(geno), 1, all)
    if ("trait.adjusted" %in% names(ped)) 
        missidx <- missidx | is.na(ped$trait.adjusted)
    if (sum(missidx) > 0) {
        ped <- ped[!missidx, ]
        kinmat <- kinmat[!missidx, !missidx]
        kinmatX <- kinmatX[!missidx, !missidx]
        geno <- geno[!missidx, ]
    }
    gvec <- chromvec <- nvariant <- noninform <- kstat <- kpvaldav <- bstat <- bpval <- NULL
    for (g in unique(map$gene)) {
        if (verbose) {
            cat("test on gene ", g, "\n")
        }
        gidx <- which(map$gene == g)
        genosub <- geno[, gidx, drop = FALSE]
        resid <- ped$trait - ped$trait.adjusted
        sex <- ped$sex
        chrom <- map$chrom[gidx[1]]
        ccfactor <- quadfactorLF(if (chrom == "X") 
            kinmatX
        else kinmat, chrom, resid, sex, male.dose)
        c.factor<-ccfactor$c.factor
        pgstat <- pedgeneLF.stats(genosub, as.vector(c.factor), 
            map$chrom[gidx[1]], male.dose, sex, resid, weights = weights[gidx], 
            acc.davies = acc.davies)
        if (pgstat$nvariant == 0) {
            cat("gene: '", g, "' has no markers after removing markers with all same genotype\n")
        }
        gvec <- c(gvec, g)
        chromvec <- c(chromvec, chrom)
        nvariant <- c(nvariant, pgstat$nvariant)
        noninform <- c(noninform, pgstat$noninform)
        kstat <- c(kstat, pgstat$stat.kernel)
        kpvaldav <- c(kpvaldav, pgstat$pval.kernel.davies)
        bstat <- c(bstat, pgstat$stat.burden)
        bpval <- c(bpval, pgstat$pval.burden)
    }
    pgdf <- data.frame(gene = gvec, chrom = chromvec, n.variant = nvariant, 
        n.noninform = noninform, stat.kernel = kstat, pval.kernel.davies = kpvaldav, 
        stat.burden = bstat, pval.burden = bpval)
    options(saveOpt)
    pglist <- list(pgdf = pgdf, call = call, kinmatX = kinmatX, kinmat = kinmat, resid=resid, KP=pgstat$pval.kernel, df=pgstat$df.kernel,
                   varz=pgstat$varz, scale=pgstat$scale, eQ=pgstat$eQ, fRmat=pgstat$fRmat,  VQ=pgstat$VQ ,maf=pgstat$maf, cfactor=c.factor,
                   statnum=pgstat$statnum, statdenom=pgstat$statdenom, genetcor=ccfactor$genet.cor, factorsum=pgstat$factorsum , sfactor=ccfactor$sexfactor  )
    class(pglist) <- "pedgene"
    return(pglist)
}



pedgeneLF.stats=
function (geno, c.factor, chrom, male.dose, sex, resid, weights = NULL, 
    acc.davies = 1e-06) 
{
    x.chrom <- as.character(chrom) == "X"
    v <- apply(geno, 2, var, na.rm = TRUE)
    nvariant0 <- ncol(geno)
    geno <- geno[, v > 0, drop = FALSE]
    geno <- as.matrix(geno)
    nvariant <- ncol(geno)
    nvariant.noninform <- nvariant0 - nvariant
    if (nvariant == 0) {
        return(list(stat.kernel = NA, df.kernel = NA, pval.kernel = NA, 
            pval.kernel.davies = NA, stat.burden = NA, pval.burden = NA, 
            nvariant = nvariant, noninform = nvariant.noninform))
    }
    col.miss <- apply(is.na(geno), 2, any)
    if (any(col.miss == TRUE)) {
        for (j in 1:ncol(geno)) {
            if (col.miss[j]) {
                if (x.chrom) {
                  mn.male <- mean(geno[sex == 1, j], na.rm = TRUE)
                  geno[is.na(geno[, j]) & sex == 1, j] <- mn.male
                  mn.female <- mean(geno[sex == 2, j], na.rm = TRUE)
                  geno[is.na(geno[, j]) & sex == 2, j] <- mn.female
                }
                else {
                  mn <- mean(geno[, j], na.rm = TRUE)
                  geno[is.na(geno[, j]), j] <- mn
                }
            }
        }
    }
    if (x.chrom) {
        count.male <- apply(geno[sex == 1, ], 2, sum)
        count.female <- apply(geno[sex == 2, ], 2, sum)
        n.male <- sum(sex == 1)
        n.female <- sum(sex == 2)
        maf <- (count.male + count.female)/(n.male + 2 * n.female)
    }
    else {
        maf <- apply(geno/2, 2, mean)
    }
    if (is.null(weights)) {
        wt <- 1/sqrt(maf * (1 - maf))
    }
    else {
        wt <- weights[v > 0]
    }
    r.mat <- cor(geno)
    f <- wt * sqrt(maf * (1 - maf))
    fRmat <- (f %o% f) * r.mat
    var.z <- fRmat * c.factor
    e.Q <- sum(diag(var.z))
    var.Q <- 2 * sum(diag(var.z %*% var.z))
    if (x.chrom & (male.dose != 1)) {
        geno.score <- geno
        geno.score[sex == 1, ] <- geno[sex == 1, ] * male.dose
        kmat <- geno.score %*% diag(wt^2) %*% t(geno.score)
        burden.score.subject <- as.vector(geno.score %*% wt)
    }
    else {
        kmat <- geno %*% diag(wt^2, nrow = length(wt), ncol = length(wt)) %*% 
            t(geno)
        burden.score.subject <- as.vector(geno %*% wt)
    }
    stat.num <- (resid %*% burden.score.subject)^2
    factor.sum <- sum(fRmat)
    stat.denom <- factor.sum * c.factor
    burden.stat <- stat.num/stat.denom
    burden.pval <- pchisq(burden.stat, 1, lower.tail = FALSE)
    if (nvariant > 1) {
        stat.kernel <- as.vector(resid %*% kmat %*% resid)
        scale <- 2 * e.Q/var.Q
        df <- 2 * e.Q^2/var.Q
        pval.kernel <- pchisq(stat.kernel * scale, df = df, lower.tail = FALSE)
        eig <- eigen(var.z, symmetric = T, only.values = T)
        evals <- eig$values[eig$values > 1e-06 * eig$values[1]]
        pval.kernel.davies <- davies(stat.kernel, evals, acc = acc.davies)$Qq
        if ((pval.kernel.davies > 1) | (pval.kernel.davies < 
            0)) {
            pval.kernel.davies <- NA
        }
    }
    else {
        stat.kernel <- burden.stat
        pval.kernel <- pval.kernel.davies <- burden.pval
    }
    lst <- list(stat.kernel = stat.kernel, df.kernel = df, pval.kernel = pval.kernel, 
        pval.kernel.davies = pval.kernel.davies, stat.burden = burden.stat, 
        pval.burden = burden.pval, nvariant = nvariant, noninform = nvariant.noninform, varz=var.z, scale=scale, eQ = e.Q,
        fRmat=fRmat,  VQ=var.Q ,maf=maf, statnum=stat.num, statdenom=stat.denom, factorsum=factor.sum  )
    return(lst)
}

quadfactorLF=
function (kinmat, chrom, resid, sex, male.dose) 
{
    if (chrom == "X") {
        sex.factor <- 2 * (sex == 2) %o% (sex == 2) + male.dose^2 * 
            (sex == 1) %o% (sex == 1) + sqrt(2) * male.dose * 
            ((sex == 2) %o% (sex == 1) + (sex == 1) %o% (sex == 
                2))
    }
    else {
        sex.factor <- 2
    }
    genet.var <- 2 * kinmat
    d <- sqrt(diag(genet.var))
    genet.cor <- sex.factor * (genet.var/(d %o% d))
    c.factor <- t(resid) %*% genet.cor %*% resid
    list<-list(c.factor=c.factor,genet.cor=genet.cor, sexfactor=sex.factor)
    return(list)
}
########################################################################################################
########################################################################################################
### DJ Schaid
########################################################################################################
########################################################################################################









#########################################################################################################
#########################################################################################################
#Simulation=1683
Simulation=5
r=2
wt=1
acc.davies = 1e-05
#######################################################################################################
#######################################################################################################
family="binomial"

corstr="exchangeable"

#######################################################################################################
#######################################################################################################
CC="PC"

file=paste("D:/Documents/code/Kernel+Burden/Kernel+Burden/FDataGene1")

#######################################################################################################

GEER=matrix(1,Simulation,2)

#######################################
# DataR
#######################################

  KQ=matrix(0,Simulation,1)
  BQ=matrix(0,Simulation,1)
  BAA=matrix(0,Simulation,1)
  BAAP=matrix(1,Simulation,1)
  KAA=matrix(0,Simulation,1)
  KAAP=matrix(1,Simulation,1)
  KAAPD=matrix(1,Simulation,1)

######################################################################################################
  
  ###################################
  # DataR
  ###################################  
  GEEcoeff=matrix(0,Simulation,5)

 

##################################################################
##################################################################
DataJJ=matrix(0,Simulation,1)
####################################
####################################

Stat=matrix(0,Simulation,4)
#MMAF=read.csv("D:/rare Data/final Data describe 1030 gene/HHEoutput3_1030gene_MAF_MAP_GeneID.csv", header = F)
MMAF=read.csv("D:/Documents/code/Kernel+Burden/Kernel+Burden/HHEoutput3_MAF_MAP_GeneID.csv", header = F)
####################################
####################################

Stat[,1]=t(t(1:Simulation) )

for (J in 1:Simulation)

{

################################################
Stat[J,4]=sum( MMAF[MMAF[,3]==J,1]>=0.05 )
Stat[J,3]=sum( MMAF[MMAF[,3]==J,1]>0)
################################################


Data=read.table(paste(file,"/FHdaffected",J,".txt",sep=""), header = F)

 if (  (  sum(Data[,8:length(Data[1,]) ])>0 )& (length( Data[1,] )>9 ) )
       {
         if ( sum( colSums(Data[,seq(8,length(Data[1,]),by=2)]+Data[,seq(9,length(Data[1,]),by=2)] )!=0 )>1 )
             { DataJJ[J,1]=1 }
       }  
Stat[J,2]=( length(Data[1,])-7 )/2
}

DataJJ=t(t(1:Simulation))*DataJJ
DataJJ1=DataJJ[DataJJ>0,1]

DataJJ1
rm(list=c('DataJJ','Data') )










##########################################################################################################


for ( J in DataJJ1 )



{

print(J)

###########################################################################################################
# Data
###########################################################################################################

Data=read.table(paste(file,"/FHdaffected",J,".txt",sep=""), header = F)

########################################
## COVX
########################################
COVXR=read.table(paste(file,"/FHdaffected_COVX",J,".txt",sep=""), header = F)
########################################


###########################
nF=max(Data[,1])
###########################


nnP=matrix(0, max(Data[,1]),1)

   for ( JJ in 1: max(Data[,1]) )
    {
        nnP[JJ,1]=sum( Data[,1]==JJ )/2
    } 

rm(JJ)

nMAF=(length(Data[1,])-7)/2
sumnnP=sum(nnP)


DataR=Data
DDR=DataR[, seq( 8, (nMAF*2+7), 2)]+DataR[,seq(9,(nMAF*2+7), 2)] 
 
############################################################################


###########################################################################################################
## GEE
###########################################################################################################

if (nMAF>1)
{ 
 GEER[J,1]=summary( gee(DataR[,7] ~COVXR[,1]+COVXR[,2]+ t( t( rowSums(DDR) ) ), id=DataR[,1], family=family, corstr=corstr) )[[7]][20]
 GEER[J,2]=2*(1-pnorm( abs( GEER[J,1]) ) )
}

###############################################################################
###############################################################################
 examplemap=read.table("D:/Documents/code/Kernel+Burden/Kernel+Burden/examplemap0.txt", header = T)
###############################################################################
 examplemap=examplemap[1:nMAF,]
###############################################################################
###############################################################################

kinmat=matrix(0, sumnnP, sumnnP)

for (  JJ in 1:length(nnP) )
    {
        
            if (JJ==1)
              {   
                  kinmat[1:nnP[1,1],1:nnP[1,1]]=0.25
              }
            if (JJ>1)
              {
                 kinmat[ ( sum(nnP[1:(JJ-1),1])+1 ):  sum(nnP[1:JJ,1]) , ( sum(nnP[1:(JJ-1),1])+1 ):  sum(nnP[1:JJ,1]) ]=0.25

              }

     }

rm(JJ)
diag( kinmat)=0.5;

 
  ########################################
  # DataR
  ########################################
      GEEcoeff[J,]=summary( gee(DataR[,7] ~COVXR[,1]+COVXR[,2] , id=DataR[,1], family=family, corstr=corstr) )[[7]][1:5]  

  ########################################
  # DataR
  ########################################
     workingcorrelation=summary( gee(DataR[,7] ~ COVXR[,1]+COVXR[,2], id=DataR[,1], family=family, corstr=corstr) )[[8]]






######################################################################################################
## mu
######################################################################################################
if ( family =="binomial" )
{
   

           ########################################
           # DataR
           ########################################
                mu=t(  t( exp( COVXR[,2]*GEEcoeff[J,3]+COVXR[,1]*GEEcoeff[J,2]+GEEcoeff[J,1] )/(1+exp( COVXR[,2]*GEEcoeff[J,3]+COVXR[,1]*GEEcoeff[J,2]+GEEcoeff[J,1]  ) )   )    )

    
}

   
######################################################################################################
######################################################################################################
if (wt==1)
{
  weight=rep(1,1,nMAF)
}
 

######################################################################################################
######################################################################################################




if (  sum( examplemap[,2]=="AA" )>0  )
{


IDAA=1:nMAF
IDAA=IDAA[ examplemap[,2]=="AA" ]


       ########################################
       # DataR
       ########################################

               IDDDR=IDAA[ colSums(DDR[, IDAA] )!=0]

   

  weightt=weight[IDDDR]
  ########################################
  # DataR
  ########################################
    
           DDRmaf <- apply(DDR[, IDDDR]/2, 2, mean)

           DDRr.mat <- cor(DDR[,IDDDR])
           DDRf <- weightt*sqrt(DDRmaf * (1 -DDRmaf))
           DDRfRmat <- (DDRf %o% DDRf) * DDRr.mat
           DDRfRmatt= sum( sum( DDRfRmat) )

  

#############################################
QQ=matrix(0,length(IDDDR),nF)
BQC=matrix(0,nF,1)
#############################################


  
   for ( nnF in 1:nF )
     {
         
       ##########################################################
       ## binomial
       ##########################################################    
        if ( family=="binomial" )
             {
                 if (nnF==1)
                      { 
                         
                         ###################################
                         # DataR
                         ###################################     
                           
                           Yi=DataR[1:(nnP[nnF,1]*r),7]
                           mui=mu[1:(nnP[nnF,1]*r),1]
                           stvi= sqrt(  mui*(1-mui) )
                           Vi=diag( stvi )%*%workingcorrelation[1:(nnP[nnF,1]*r), 1:(nnP[nnF,1]*r)]%*%diag(stvi)
                           ai=diag( mui*(1-mui) )
                           Gi=DDR[1:(nnP[nnF,1]*r), IDDDR ]
                           QQ[ ,nnF]=t(Gi)%*%ai%*%solve(Vi)%*%(Yi-mui)

                           kinmati=kinmat[ 1:nnP[nnF,1],1:nnP[nnF,1] ] 
                           genetvari <- 2 * kinmati
                           di<- sqrt(diag(genetvari))
                           genetcori <-(genetvari/(di %o% di))

                           ###############################
                           if (nnP[nnF,1]>1)
                           { 
                             genetcorii=genetcori[ rep(1:nrow(genetcori),each=r), rep(1:ncol(genetcori),each=r) ] 
                           }
                           if ( nnP[nnF,1]==1 )
                           {
                             genetcorii=matrix(genetcori, r,r)
                           }
                           ################################

                           BQC[nnF,1]=t( (Yi-mui) )%*%ai%*%solve(Vi)%*%genetcorii%*%solve(Vi)%*%ai%*%(Yi-mui)
                           
                           rm( list=c('Yi','mui','stvi','Vi','ai','Gi','kinmati','genetvari','di','genetcori','genetcorii' ) )

                        
                        }


                  if (nnF>1)
                       {

                         ###################################
                         # DataR
                         ###################################     
                    
                           Yi=DataR[ ( sum( nnP[ 1: ( nnF-1) ,1] )*r+1 ): ( sum( nnP[ 1: nnF ,1] )*r ) ,7]
                           mui=mu[ ( sum( nnP[ 1: ( nnF-1) ,1] )*r+1 ):   (  sum( nnP[ 1: nnF ,1] )*r) ,1]
                           stvi= sqrt(  mui*(1-mui) )
                           Vi=diag( stvi )%*%workingcorrelation[1:(nnP[nnF,1]*r), 1:(nnP[nnF,1]*r)]%*%diag(stvi)
                           ai=diag( mui*(1-mui) )
                           Gi=DDR[  ( sum( nnP[ 1: ( nnF-1) ,1] )*r+1 ):   (  sum( nnP[ 1:  nnF ,1] )*r) , IDDDR ]
                           QQ[ ,nnF]=t(Gi)%*%ai%*%solve(Vi)%*%(Yi-mui) 


                           kinmati=kinmat[ ( sum( nnP[ 1: sum( nnF-1) ,1] )+1 ):  sum( nnP[ 1: sum( nnF ) ,1] )  ,
                                           ( sum( nnP[ 1: sum( nnF-1) ,1] )+1 ):  sum( nnP[ 1: sum( nnF ) ,1] )  ] ;
                           genetvari <- 2 * kinmati
                           di<- sqrt(diag(genetvari))
                           genetcori <-(genetvari/(di %o% di))

                           ###############################
                           if (nnP[nnF,1]>1)
                           { 
                             genetcorii=genetcori[ rep(1:nrow(genetcori),each=r), rep(1:ncol(genetcori),each=r) ] 
                           }
                           if( nnP[nnF,1]==1 )
                           {
                             genetcorii=matrix(genetcori,r,r)
                           }    
                           ##############################
                           

                           BQC[nnF,1]=t( (Yi-mui) )%*%ai%*%solve(Vi)%*%genetcorii%*%solve(Vi)%*%ai%*%(Yi-mui)
                           
                           rm( list=c('Yi','mui','stvi','Vi','ai','Gi','kinmati','genetvari','di','genetcori','genetcorii' ) )
         

                        }

          ############################################################     
               }
          # binomial
          ############################################################  


       ############################################################### 
        }
       # for (nnF in 1:nF)
       ###############################################################




########################################
# DataR
########################################
  
  #################### 
  #Burden
  ####################
     BQ[J,1]= sum(  rowSums(QQ)* weightt   )^2 
     BAA[J,1]=BQ[J,1]/( sum( BQC )*2*DDRfRmatt )
     BAAP[J,1]= pchisq( BAA[J,1] , 1, lower.tail = FALSE)

  ####################
  #Kernel
  ####################
     KQ[J,1]= sum(   (  rowSums(QQ)* weightt   )^2      ) 
     VZQ=DDRfRmat*2*sum(BQC)
     EQ=sum(  diag( VZQ )  )
     VQ=2*sum(  diag( VZQ%*%VZQ )   )
     scaleK=2*EQ/VQ
     dK=2*EQ^2/VQ
     KAA[J,1]=KQ[J,1]*scaleK
     KAAP[J,1]=pchisq( KAA[J,1], dK, lower.tail=FALSE)

     eig <- eigen(VZQ  , symmetric = T, only.values = T)
     evals <- eig$values[eig$values > 1e-06 * eig$values[1]]
     KAAPD[J,1] <- davies(KQ[J,1], evals, acc = acc.davies)$Qq


   
########################################################################
}
#if (  sum( examplemap[,2]=="AA" )>0  )
########################################################################



rm( list=c('DDRf','DDRfRmat','DDRfRmatt',
'DDRmaf','DDRr.mat','dK','eig','EQ','evals',
'IDDDR','scaleK','kinmat',
'VQ','VZQ','weightt','QQ',
'BQC','IDAA' ) )




rm( list=c('DDR',
'examplemap',
'mu',
'workingcorrelation',
'DataR',
'nnF', 'nnP', 
'sumnnP',  'weight', 'Data', 'nMAF') ) 



#########################################################################
### for (J in 1:Simulation)
}
#########################################################################





       PP_wt1_CX0=cbind(KAAP,KAAPD,BAAP,GEER[,2])
      
       if (CC=="PC")
       { 
         write.table( PP_wt1_CX0, file = paste( file,"/COVXSEXAGE_LFPP_wt1_CX0_c",corstr,".txt",sep=""), row.names=F, col.names=F, append=F )
         write.table( DataJJ1, file = paste( file,"/COVXSEXAGE_DataJJ1.txt",sep=""), row.names=F, col.names=F, append=F )
         write.table( Stat, file = paste( file,"/COVXSEXAGE_Stat.txt",sep=""), row.names=F, col.names=F, append=F )
       }
       
       RPP_wt1_CX0=colSums( PP_wt1_CX0[DataJJ1, ]<0.05 & PP_wt1_CX0[DataJJ1, ]>=0)/length(DataJJ1)

       if (CC=="PC")
       {
          write.table( RPP_wt1_CX0, file = paste(file,"/COVXSEXAGE_LFRPP_wt1_CX0_c",corstr,".txt",sep=""), row.names=F, col.names=F, append=F )
       }
       
       print( RPP_wt1_CX0 )

     


